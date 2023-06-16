#include <iostream>
#include <lf_queue/lf_queue.hpp>

using namespace lockFreeQueue;
using namespace lockFreeQueueProcessor;

#ifndef NTASKS
#define NTASKS 1000
#endif

int main(int argc, char* argv[]) {
    if(!parser::parse(argc, argv)) return 0;
    LfQueue<int> queue(parser::bufsize);
    parser::Consumed.clear();

    std::vector<std::thread> threads;

    for (int i = 0; i < parser::nprodthreads; ++i) {
        threads.emplace_back(produce, std::ref(queue), parser::prodtime);
    }

    for (int i = 0; i < parser::nconsthreads; ++i) {
        threads.emplace_back(consume, std::ref(queue), parser::constime);
    }

    for (std::thread& thread : threads) {
        thread.join();
    }

    if(parser::Consumed.size() == NTASKS + 1 || parser::ntasks == -1) {
        std::cout << "everything's good" << std::endl;
    } else {
        std::cout << "smth went wrong" << std::endl;
    }
}