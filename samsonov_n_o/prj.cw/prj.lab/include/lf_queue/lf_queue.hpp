#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>

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
            std::atomic<unsigned> sequence; /**< Порядковый номер ячейки */
            T data;                         /**< Данные, хранящиеся в ячейке */
        };
    
    private:
        alignas(64) std::vector<CellTy> buffer;                   /**< Буфер очереди */
        alignas(64) unsigned buffer_mask;                         /**< Маска, чтобы гарантировать, что границы не превышены */
        alignas(64) std::atomic<unsigned> enqueuePos, dequeuePos; /**< позиции головы и хвоста для установки/удаления объектов очереди */

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

    /* Implementation of the LfQueue class */

    template <typename T>
    LfQueue<T>::LfQueue(unsigned BufSize) : buffer(BufSize), buffer_mask(BufSize - 1) {
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
            buffer[i].sequence.store(i, std::memory_order_relaxed); // fill in the initial sequence
        }
        enqueuePos.store(0, std::memory_order_relaxed);
        dequeuePos.store(0, std::memory_order_relaxed);
    }

    template <typename T>
    bool LfQueue<T>::push(T data) {
        CellTy* cell;
        unsigned Pos; // current position to add element
        bool Res = false; // method call state
        // CAS-loop
        while (!Res) {
            Pos = enqueuePos.load(std::memory_order_relaxed); // Getting the current position where we put the element
            
            // the buffer is cyclic, so you can't write to cell &buffer[Pos % buffer_mask]
            // small performance optimization due to the fact that it will give a power of two
            cell = &buffer[Pos & buffer_mask]; // remember unique cell
            
            auto Seq = cell->sequence.load(std::memory_order_acquire); // Getting the sequence number of the current cell
            auto Diff = static_cast<int>(Seq) - static_cast<int>(Pos); // To check if Pos is exceeded by Seq

            // the queue is full or the queue has moved forward in a circle
            // if at least 1 producer managed to push
            if (Diff < 0) {
                return false;
            }
            // If sequence was not affected by other producers ()
            // check if it is possible to increase the position of the cell in the queue
            if (Diff == 0) {
                // the second (default) memory model is std::memory_order_seq_cst (is it possible to relax?)
                Res = enqueuePos.compare_exchange_weak(Pos, Pos + 1, std::memory_order_relaxed);
            }
        }
        
        // move element to head and write to sequence
        cell->data = std::move(data);
        cell->sequence.store(Pos + 1, std::memory_order_release);
        return true;
    }

    template <typename T>
    bool LfQueue<T>::pop(T &data) {
        CellTy* cell;
        unsigned Pos;
        bool Res = false;

        while (!Res) {
            // get the current position from which to remove the element from the queue
            Pos = dequeuePos.load(std::memory_order_relaxed);
            cell = &buffer[Pos & buffer_mask];
            auto Seq = cell->sequence.load(std::memory_order_acquire);
            auto Diff = static_cast<int>(Seq) - static_cast<int>(Pos + 1);

            // if the queue is empty, then return without entering the CAS-loop
            if (Diff < 0) {
                return false;
            }
            // Checking if Seq has been modified by other producers
            // and has not been modified by consumers
            // and can we increment Pos
            if (Diff == 0) {
                Res = dequeuePos.compare_exchange_weak(Pos, Pos + 1);
            }
        }

        // read and update element for next buffer cycle
        data = std::move(cell->data);
        cell->sequence.store(Pos + buffer_mask + 1, std::memory_order_release);
        return true;
    }

    template<typename T>
    bool LfQueue<T>::is_empty() const {
        return enqueuePos.load() == dequeuePos.load();
    }

} // namespace lockFreeQueue

namespace lockFreeQueueProcessor {
    using namespace lockFreeQueue;
    
    std::atomic<int> NTasks; // Количество задач
    std::vector<int> Consumed; // Вектор потреблённых задач
    std::mutex ConsMut; // Блокировка для потребления задач 

    /**
     * \brief Добавление задач в конец очереди
     * \param queue Ссылка на очередь, в которую будут добавлены задачи
    */
    void produce(LfQueue<int>& queue, int ctime = 0) {
        for (;;) {
            int N = NTasks.load();

            // checking for the need to enter the CAS-loop
            if (N < 0) {
                break;
            }
            while (!NTasks.compare_exchange_weak(N, N - 1, std::memory_order_relaxed)) {
                // recheck to avoid data-races
                if (N < 0) {
                    return;
                }
                std::this_thread::yield();
            }
            while (!queue.push(N)) { // trying to push
                std::this_thread::yield();
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(ctime));
        }
    }

    /**
     * \brief Потребление задач из начала очереди
     * \param queue Ссылка на очередь, из которой будут потреблены задачи
    */
    void consume(LfQueue<int>& queue, int ptime = 0) {
        for (;;) {
            int N = NTasks.load();
            if (N < 0 && queue.is_empty()) {
                break;
            }
            bool Succ = queue.pop(N); // trying to pop
            if (Succ) {
                // a record of what was consumed by consumers
                std::lock_guard<std::mutex> Lk{ConsMut};
                Consumed.push_back(N); // if pop succeeded, then write to Consumed
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(ptime));
        }
    }

} // namespace lockFreeQueueProcessor

namespace parser {
    int NTasks = 1000;
    int BufSize = 128;
    int ConsTime = 0;
    int ProdTime = 0;
    
    int parse(int argc, char* argv[]);
}