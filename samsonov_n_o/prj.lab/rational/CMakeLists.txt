add_library(rational include/rational/rational.hpp rational.cpp)

target_include_directories(rational PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
install(TARGETS rational)
