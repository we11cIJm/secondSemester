#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>
#include <chrono>
#include <map>
#include <functional>

namespace lockFreeQueue {
    
    /**
     * \class Класс LfQueue (Lock-free очередь)
     * \details Класс представляет собой ограниченную очередь, которая может использоваться несколькими потоками одновременно.
    */
    template <typename T>
    class LfQueue {
    private:
        /**
         * \brief Структура ячейки LfQueue
        */
        struct CellTy {
            std::atomic<unsigned> sequence; /// Порядковый номер ячейки
            T data;                         /// Данные, хранящиеся в ячейке
        };
    
    private:
        alignas(64) std::vector<CellTy> buffer_;                    /// Буфер очереди
        alignas(64) unsigned buffer_mask_;                          /// Маска, чтобы гарантировать, что границы не превышены
        alignas(64) std::atomic<unsigned> enqueuePos_, dequeuePos_; /// позиции головы и хвоста для установки/удаления объектов очереди

    public:

        /**
         * \brief Конструктор LfQueue
         * \param BufSize Размер буфера
         * \throw std::runtime_error, когда размер буфера не соответвует документации
        */
        explicit LfQueue(unsigned BufSize);

        /**
         * \brief Деструктор
        */
        ~LfQueue() = default;

        /**
         * \brief Добавление элемента в конец буфера
         * \tparam data Новый элемент очереди
         * \return Статус вызова метода (успешно/неудачно)
        */
        bool push(T data);

        /**
         * \brief Удаление элемента из начала буфера
         * \tparam data Элемент для удаления из очереди
         * \return Статус вызова метода (успешно/неудачно)
        */
        bool pop(T& data);

        /**
         * \brief Проверка пустоты очереди
         * \return Состояние очереди (путая/не пустая)
        */
        bool is_empty() const;
    };

    /* Реализация класса LfQueue */

    template <typename T>
    LfQueue<T>::LfQueue(unsigned BufSize) : buffer_(BufSize), buffer_mask_(BufSize - 1) {
        if (BufSize > (1 << 30)) {
            throw std::runtime_error("buffer size too large");
        }
        if (BufSize < 2) {
            throw std::runtime_error("buffer size too small");
        }
        if ((BufSize & (BufSize - 1)) != 0) {
            throw std::runtime_error("buffer size is not power of 2");
        }
        for (unsigned i = 0; i != BufSize; ++i) {
            buffer_[i].sequence.store(i, std::memory_order_relaxed); // заполнение изначальной последовательности
        }
        enqueuePos_.store(0, std::memory_order_relaxed);
        dequeuePos_.store(0, std::memory_order_relaxed);
    }

    template <typename T>
    bool LfQueue<T>::push(T data) {
        CellTy* cell;
        unsigned position; // текущая позиция для добавления элемента
        bool result = false; // статус метода
        // CAS-цикл
        while (!result) {
            position = enqueuePos_.load(std::memory_order_relaxed); // получение текущей позиции
            
            cell = &buffer_[position & buffer_mask_]; //запоминаем уникальный номер ячейки (для кругового прохода)
            
            auto Seq = cell->sequence.load(std::memory_order_acquire); // получение текущего уникального номера
            auto Diff = static_cast<int>(Seq) - static_cast<int>(position);

            // очередь полна или произошёл круговой проход
            // если хотя бы 1 производитель успел запушить
            if (Diff < 0) {
                return false; // continue?
            }

            if (Diff == 0) {
                // вторая (по умолчанию) модель памяти — std::memory_order_seq_cst (можно ли ее ослабить?)
                result = enqueuePos_.compare_exchange_weak(position, position + 1, std::memory_order_relaxed);
            }
        }
        
        // обновление позиции
        cell->data = std::move(data);
        cell->sequence.store(position + 1, std::memory_order_release);
        return true;
    }

    template <typename T>
    bool LfQueue<T>::pop(T& data) {
        CellTy* cell;
        unsigned position;
        bool result = false;

        while (!result) {
            position = dequeuePos_.load(std::memory_order_relaxed);
            cell = &buffer_[position & buffer_mask_];
            auto Seq = cell->sequence.load(std::memory_order_acquire);
            auto Diff = static_cast<int>(Seq) - static_cast<int>(position + 1);

            // проверка пустоты очереди перед входом в CAS
            if (Diff < 0) {
                return false;
            }
            // Проверка того, был ли Seq изменен другими производителями
            // и не был ли изменен потребителями
            if (Diff == 0) {
                result = dequeuePos_.compare_exchange_weak(position, position + 1, std::memory_order_relaxed);
            }
        }

        // обновление элемента для следующего буферного цикла
        data = std::move(cell->data);
        cell->sequence.store(position + buffer_mask_ + 1, std::memory_order_release);
        return true;
    }
    
    template<typename T>
    bool LfQueue<T>::is_empty() const {
        return enqueuePos_.load() == dequeuePos_.load();
    }

} // namespace lockFreeQueue

namespace parser {
    std::atomic<int> ntasks{1000};  /// Количество задач
    std::vector<int> Consumed;      /// Вектор потреблённых задач
    std::mutex ConsMut;             /// Блокировка для потребления задач
    unsigned int bufsize{4096};      /// Размер буфера
    unsigned int constime{0};       /// Время на потребление задачи
    unsigned int prodtime{0};       /// Время на производство задачи
    unsigned int nprodthreads{1};   /// Количество производящих потоков
    unsigned int nconsthreads{1};   /// Количество потребляющих потоков 

    /**
     * \brief Парсер переданных опций для очереди
    */
    bool parse(int argc, char** argv) {
        std::map<std::string, std::string> arguments;

        for (int i = 1; i < argc; ++i) {
            arguments[argv[i]] = (i + 1 < argc) ? argv[i + 1] : "";
        }
        arguments.count("--ntasks") > 0 ? ntasks = std::stoi(arguments["--ntasks"]) : ntasks = 1000;
        arguments.count("--bufsize") > 0 ? bufsize = std::stoi(arguments["--bufsize"]) : bufsize = 4096;
        arguments.count("--constime") > 0 ? constime = std::stoi(arguments["--constime"]) : constime = 0;
        arguments.count("--prodtime") > 0 ? prodtime = std::stoi(arguments["--prodtime"]) : prodtime = 0;
        arguments.count("--nprodthreads") > 0 ? nprodthreads = std::stoi(arguments["--nprodthreads"]) : nprodthreads = 1;
        arguments.count("--nconsthreads") > 0 ? nconsthreads = std::stoi(arguments["--nconsthreads"]) : nconsthreads = 1;

        if (arguments.count("--help") > 0 || argc == 1) {
            std::cout << "Опции:" << std::endl;
            std::cout << "--ntasks = " << ntasks << " : количество задач" << std::endl;
            std::cout << "--bufsize = " << bufsize << " : размер буфера очереди" << std::endl;
            std::cout << "--constime = " << constime << " : время для потребления одной задачи" << std::endl;
            std::cout << "--prodtime = " << prodtime << " : время для производства одной задачи" << std::endl;
            std::cout << "--nprodthreads = " << nprodthreads << " : количество производственных потоков" << std::endl;
            std::cout << "--nconsthreads = " << nconsthreads << " : количество потребительных потоков" << std::endl;
            return false;
        }

        return true;
    }
} // namespace parser


namespace lockFreeQueueProcessor {

    /**
     * \brief Функция для замера времени выполнения produce/consume
     * \tparam func - одна из функций (produce/consume), argc - std::ref(<Объект LfQueue>), prodtime/constime
     * \return Время исполнения одной из функций (produce/consume)
    */
    template <typename Func, typename... Args>
    std::chrono::milliseconds measureDuration(Func func, Args&&... args) {
        auto start = std::chrono::high_resolution_clock::now();
        func(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    /**
     * \fn void produce(LfQueue<int>& queue, int ctime = constime)
     * \brief Добавление задач в конец очереди
     * \param queue Ссылка на очередь, в которую будут добавлены задачи
    */
    void produce(lockFreeQueue::LfQueue<int>& queue, int ctime = parser::constime) {
        for (;;) {
            int N = parser::ntasks.load();

            // проверка на необходимость входа в CAS
            if (N < 0) {
                break;
            }
            while (!parser::ntasks.compare_exchange_weak(N, N - 1, std::memory_order_relaxed)) {
                // повторная проверка, чтобы избежать гонок данных
                if (N < 0) {
                    return;
                }
                std::this_thread::yield();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(ctime));            
            while (!queue.push(N)) { // trying to push
                std::this_thread::yield();
            }
            
        }
    }

    /**
     * \fn void consume(LfQueue<int>& queue, int ptime = prodtime)
     * \brief Потребление задач из начала очереди
     * \param queue Ссылка на очередь, из которой будут потреблены задачи
    */
    void consume(lockFreeQueue::LfQueue<int>& queue, int ptime = parser::prodtime) {
        for (;;) {
            int N = parser::ntasks.load();
            if (N < 0 && queue.is_empty()) {
                break;
            }
            bool Succ = queue.pop(N); // пытаемся сделать pop
            if (Succ) {
                // запись того, что было потреблено потребителями
                std::lock_guard<std::mutex> Lk{parser::ConsMut};
                parser::Consumed.push_back(N); // если получился pop, то пишем в Consumed
            }            
            std::this_thread::sleep_for(std::chrono::milliseconds(ptime));
        }
    }

} // namespace lockFreeQueueProcessor
