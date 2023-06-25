enable_testing()

option(TESTING_MODE "Enable testing mode" OFF)

add_executable(example example.cpp)
target_link_libraries(example PRIVATE lf_queue)

if (TESTING_MODE)
    find_package(GTest CONFIG REQUIRED)
    message("Testing mode enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -g")
    set_source_files_properties(lf_queue.test.cpp PROPERTIES COMPILE_FLAGS "-fsanitize=thread")

    add_executable(lf_queue.test lf_queue.test.cpp)
    target_link_libraries(lf_queue.test PRIVATE GTest::gtest GTest::gtest_main lf_queue)

    install(TARGETS example lf_queue.test DESTINATION bin COMPONENT test)
else (TESTING_MODE)
    install(TARGETS example DESTINATION bin COMPONENT test)
endif (TESTING_MODE)
