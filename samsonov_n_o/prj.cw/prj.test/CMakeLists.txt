enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -g")
set_source_files_properties(lf_queue.test.cpp PROPERTIES COMPILE_FLAGS "-fsanitize=thread")

add_executable(lf_queue.test lf_queue.test.cpp)
target_link_libraries(lf_queue.test PRIVATE GTest::gtest GTest::gtest_main lf_queue)

# add_executable(example example.cpp)
# target_link_libraries(example PRIVATE lf_queue)