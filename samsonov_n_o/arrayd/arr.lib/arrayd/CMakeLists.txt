add_library(arrayd arrayd.cpp include/arrayd/arrayd.hpp) # adding a library
set_property(TARGET arrayd PROPERTY PUBLIC_HEADER arrayd.hpp)
# setting a property: target(executable or library), property(public or private)

# what this things below are doing?
target_include_directories(arrayd PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
install(TARGETS arrayd)
