#include <thread>

#include <gtest/gtest.h>

#include <lf_queue/lf_queue.hpp>

using namespace lockFreeQueue;
using namespace lockFreeQueueProcessor;

#ifndef NTASKS
#define NTASKS 1000
#endif

#ifndef BUFSIZE
#define BUFSIZE 128
#endif

TEST(atomics, bounded_lockfree_queue_1_1) {
    NTasks = NTASKS;
    LfQueue<int> Q(BUFSIZE);
    Consumed.clear();
    std::thread t1{produce, std::ref(Q)};
    std::thread t2{consume, std::ref(Q)};
    
    t1.join();
    t2.join();
  
    EXPECT_EQ(Consumed.size(), NTASKS + 1); // [0 .. NTASKS] inclusive
    EXPECT_EQ(NTasks, -1);
}

TEST(atomics, bounded_lockfree_queue_1_2) {
    NTasks = NTASKS;
    LfQueue<int> Q(BUFSIZE);
    Consumed.clear();
    std::thread t1{produce, std::ref(Q)};
    std::thread t2{consume, std::ref(Q)};
    std::thread t3{consume, std::ref(Q)};
  
    t1.join();
    t2.join();
    t3.join();
  
    EXPECT_EQ(Consumed.size(), NTASKS + 1);
    EXPECT_EQ(NTasks, -1);
}

TEST(atomics, bounded_lockfree_queue_2_1) {
    NTasks = NTASKS;
    LfQueue<int> Q(BUFSIZE);
    Consumed.clear();
    std::thread t1{produce, std::ref(Q)};
    std::thread t2{produce, std::ref(Q)};
    std::thread t3{consume, std::ref(Q)};
  
    t1.join();
    t2.join();
    t3.join();
  
    EXPECT_EQ(Consumed.size(), NTASKS + 1);
    EXPECT_EQ(NTasks, -1);
}

TEST(atomics, bounded_lockfree_queue_2_2) {
    NTasks = NTASKS;
    LfQueue<int> Q(BUFSIZE);
    Consumed.clear();
    std::thread t1{produce, std::ref(Q)};
    std::thread t2{produce, std::ref(Q)};
    std::thread t3{consume, std::ref(Q)};
    std::thread t4{consume, std::ref(Q)};
  
    t1.join();
    t2.join();
    t3.join();
    t4.join();
  
    EXPECT_EQ(Consumed.size(), NTASKS + 1);
    EXPECT_EQ(NTasks, -1);
}

TEST(atomics, bounded_lockfree_queue_4_4) {
    NTasks = NTASKS;
    LfQueue<int> Q(BUFSIZE);
    Consumed.clear();
    std::thread t1{produce, std::ref(Q)};
    std::thread t2{produce, std::ref(Q)};
    std::thread t3{produce, std::ref(Q)};
    std::thread t4{produce, std::ref(Q)};
    std::thread t5{consume, std::ref(Q)};
    std::thread t6{consume, std::ref(Q)};
    std::thread t7{consume, std::ref(Q)};
    std::thread t8{consume, std::ref(Q)};
  
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
  
    EXPECT_EQ(Consumed.size(), NTASKS + 1);
    EXPECT_EQ(NTasks, -1);
}

TEST(atomics, bounded_lockfree_queue_20_200) {
    const int NUM_PRODUCE_THREADS = 20;
    const int NUM_CONSUME_THREADS = 200;
    NTasks = NTASKS;
    LfQueue<int> Q(BUFSIZE);
    Consumed.clear();
  
    std::vector<std::thread> threads;
  
    // Create threads
    for (int i = 0; i < NUM_PRODUCE_THREADS; ++i) {
      threads.emplace_back(produce, std::ref(Q));
    }
  
    // Create additional threads for consumption
    for (int i = 0; i < NUM_CONSUME_THREADS; ++i) {
      threads.emplace_back(consume, std::ref(Q));
    }
  
    // Join threads
    for (std::thread& thread : threads) {
      thread.join();
    }
  
    EXPECT_EQ(Consumed.size(), NTASKS + 1);
    EXPECT_EQ(NTasks, -1);
}
