add_library(rational include/rational/rational.hpp rational.cpp)

set_property(TARGET rational PROPERTY PUBLIC_HEADER rational.hpp)

target_include_directories(rational PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
install(TARGETS rational)
