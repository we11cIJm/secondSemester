#include <iostream>
#include <lf_queue/lf_queue.hpp>

using namespace lockFreeQueue;
using namespace lockFreeQueueProcessor;
using namespace parser;

#ifndef NTASKS
#define NTASKS 1000
#endif

int main(int argc, char* argv[]) {
    parse(argc, argv);
    LfQueue<int> queue(bufsize);
    Consumed.clear();

    std::vector<std::thread> threads;

    for (int i = 0; i < nprodthreads; ++i) {
        threads.emplace_back(produce, std::ref(queue), prodtime);
    }

    for (int i = 0; i < nconsthreads; ++i) {
        threads.emplace_back(consume, std::ref(queue), constime);
    }

    for (std::thread& thread : threads) {
        thread.join();
    }

    if(Consumed.size() == NTASKS + 1 || ntasks == -1)
        // std::cout << "everything good" << std::endl;
        bool a = true;
    else
        std::cout << "smth wrong" << std::endl;
}