add_library(matrixs matrixs.cpp include/matrixs/matrixs.hpp)

target_include_directories( matrixs PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
install(TARGETS matrixs)
