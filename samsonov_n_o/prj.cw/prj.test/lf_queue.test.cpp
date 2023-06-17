#include <thread>
#include <gtest/gtest.h>
#include <lf_queue/lf_queue.hpp>

using namespace lockFreeQueue;
using namespace lockFreeQueueProcessor;
using namespace parser;

#ifndef NTASKS
#define NTASKS 1000
#endif

#ifndef BUFSIZE
#define BUFSIZE 128
#endif

TEST(atomics, bounded_lockfree_queue_1_1) {
    ntasks = NTASKS;
    LfQueue<int> Q(BUFSIZE);
    Consumed.clear();
    std::thread t1{produce, std::ref(Q), 0};
    std::thread t2{consume, std::ref(Q), 0};

    t1.join();
    t2.join();

    EXPECT_EQ(Consumed.size(), NTASKS + 1); // [0 .. NTASKS] inclusive
    EXPECT_EQ(ntasks, -1);
}

TEST(atomics, bounded_lockfree_queue_1_2) {
    ntasks = NTASKS;
    LfQueue<int> Q(BUFSIZE);
    Consumed.clear();
    std::thread t1{produce, std::ref(Q), 0};
    std::thread t2{consume, std::ref(Q), 0};
    std::thread t3{consume, std::ref(Q), 0};

    t1.join();
    t2.join();
    t3.join();

    EXPECT_EQ(Consumed.size(), NTASKS + 1);
    EXPECT_EQ(ntasks, -1);
}

TEST(atomics, bounded_lockfree_queue_2_1) {
    ntasks = NTASKS;
    LfQueue<int> Q(BUFSIZE);
    Consumed.clear();
    std::thread t1{produce, std::ref(Q), 0};
    std::thread t2{produce, std::ref(Q), 0};
    std::thread t3{consume, std::ref(Q), 0};

    t1.join();
    t2.join();
    t3.join();

    EXPECT_EQ(Consumed.size(), NTASKS + 1);
    EXPECT_EQ(ntasks, -1);
}

TEST(atomics, bounded_lockfree_queue_2_2) {
    ntasks = NTASKS;
    LfQueue<int> Q(BUFSIZE);
    Consumed.clear();
    
    std::thread t1{produce, std::ref(Q), 0};
    std::thread t2{produce, std::ref(Q), 0};
    std::thread t3{consume, std::ref(Q), 0};
    std::thread t4{consume, std::ref(Q), 0};

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    EXPECT_EQ(Consumed.size(), NTASKS + 1);
    EXPECT_EQ(ntasks, -1);
}