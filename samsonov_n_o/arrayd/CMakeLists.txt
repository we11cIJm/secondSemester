cmake_minimum_required(VERSION 3.18)

set_property(GLOBAL PROPERTY USE_FOLDERS ON) # after 3.26 ON by default
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

project(arrayd)

find_package(doctest CONFIG REQUIRED)

# include_directories(arr.lib)

add_subdirectory(arr.lib)
add_subdirectory(arr.test)
