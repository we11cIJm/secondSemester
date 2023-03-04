add_executable(tests tests.cpp)
# target_link_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/../rat.lib/rational/) # path to header
target_link_libraries(tests rational doctest::doctest) # 
# add_test(NAME rat_tests COMMAND tests)

