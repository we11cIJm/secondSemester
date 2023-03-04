cmake_minimum_required(VERSION 3.18)

# option(HUNTER_ENABLED "Enable Hunter package manager support" OFF) 

set_property(GLOBAL PROPERTY USE_FOLDERS ON) # after 3.26 ON by default
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

project(rational)

find_package(doctest CONFIG REQUIRED)

add_subdirectory(rat.lib)
add_subdirectory(rat.test)

