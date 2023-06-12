#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <lf_queue/lf_queue.hpp>

using namespace lockFreeQueue;
using namespace lockFreeQueueProcessor;
using namespace parser;

int main(int argc, char* argv[]) {/*
    parse(argc, argv);
    LfQueue<int> queue(BufSize);
    std::thread th_prod{produce, std::ref(queue)};
    std::thread th_cons{consume, std::ref(queue)};

    th_prod.join();
    th_cons.join();

    return 0;
*/}