add_library(${PROJECT_NAME} INTERFACE include/lf_queue/lf_queue.hpp)

target_include_directories(${PROJECT_NAME} PUBLIC INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
