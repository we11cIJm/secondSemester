add_library(arrayd arrayd.cpp include/arrayd/arrayd.hpp)

target_include_directories(arrayd PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
install(TARGETS arrayd)
