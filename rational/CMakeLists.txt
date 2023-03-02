cmake_minimum_required(VERSION 3.24.2)

project(rational)

include_directories(rat.lib)

add_subdirectory(rat.lib)

add_subdirectory(rat.test)
