enable_testing()

option(TESTING_MODE "Enable testing mode" OFF)

if (TESTING_MODE)
    find_package(GTest CONFIG REQUIRED)
    message("Testing mode enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -g")
    set_source_files_properties(lf_queue.test.cpp PROPERTIES COMPILE_FLAGS "-fsanitize=thread")

    add_executable(lf_queue.test lf_queue.test.cpp)
    target_link_libraries(lf_queue.test PRIVATE GTest::gtest GTest::gtest_main lf_queue)
endif (TESTING_MODE)

add_executable(example example.cpp)
target_link_libraries(example PRIVATE lf_queue)

add_executable(bench bench/lf_queue_bench.cpp)
target_link_libraries(bench PRIVATE GTest::gtest GTest::gtest_main lf_queue)