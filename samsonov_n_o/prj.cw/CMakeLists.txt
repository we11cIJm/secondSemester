cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER clang++-15)
option(BUILD_DOC "Build documentation" ON)

project(
    lf_queue
    DESCRIPTION "lock-free bounded unqueue"
    LANGUAGES CXX
)

find_package(Doxygen)

if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

add_subdirectory(prj.lab)
add_subdirectory(prj.test)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/prj.lab DESTINATION lf_queueLib)
install(TARGETS ${PROJECT_NAME} example DESTINATION lf_queueLib/example)
