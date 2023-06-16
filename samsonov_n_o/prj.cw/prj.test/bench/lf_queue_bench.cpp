#include <thread>
#include <chrono>
#include <fstream>
#include <lf_queue/lf_queue.hpp>

using namespace lockFreeQueue;
using namespace lockFreeQueueProcessor;
using namespace parser;

void lockfree_queue(int argc, char** argv) {
    if(!parse(argc, argv)) return;
    std::ofstream outputFile("lf_queue.txt", std::ios::app);

    LfQueue<int> Q(bufsize);
    Consumed.clear();

    std::vector<std::thread> threads;
    std::chrono::milliseconds durationProduce;
    std::chrono::milliseconds durationConsume;

    durationProduce = measureDuration([&threads, &Q]() {
        for (int i = 0; i < nprodthreads; ++i) {
            threads.emplace_back(produce, std::ref(Q), prodtime);
        }
        for (int i = 0; i < nprodthreads && i < threads.size(); ++i) {
            threads[i].join();
        }
    });

    durationConsume = measureDuration([&threads, &Q]() {
        for (int i = 0; i < nconsthreads; ++i) {
            threads.emplace_back(consume, std::ref(Q), constime);
        }
        for (int i = nprodthreads; i < nprodthreads + nconsthreads && i < threads.size(); ++i) {
            threads[i].join();
        }
    });

    auto durationTime = std::chrono::duration_cast<std::chrono::milliseconds>(durationConsume + durationProduce);
    
    outputFile << durationProduce.count() << " " << durationConsume.count() << std::endl;

    outputFile.close();
}

int main(int argc, char** argv) {
    lockfree_queue(argc, argv);

    return 0;
}