add_library(arrayt INTERFACE include/arrayt/arrayt.hpp)

target_include_directories(arrayt PUBLIC INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
install(TARGETS arrayt)
