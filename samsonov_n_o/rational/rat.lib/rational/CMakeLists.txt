add_library(rational rational.cpp include/rational/rational.hpp) # adding a library
set_property(TARGET rational PROPERTY PUBLIC_HEADER rational.hpp)
# setting a property: target(executable or library), property(public or private)

# what this things below are doing?
target_include_directories(rational PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
install(TARGETS rational)
