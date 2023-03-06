add_executable(arr.test arr.test.cpp)
add_executable(rat.test rat.test.cpp)
target_link_libraries(arr.test arrayd doctest::doctest)
target_link_libraries(rat.test rational doctest::doctest)
