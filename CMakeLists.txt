cmake_minimum_required(VERSION 3.20)
project(da_proj1
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(da_proj1
               src/main.cpp
               src/ui.cpp
               src/utils.cpp
               src/van.cpp
               src/order.cpp
               src/dataset.cpp src/scenario1.cpp includes/scenario1.hpp includes/scenario3.hpp src/scenario3.cpp includes/scenario2.hpp src/scenario2.cpp)

add_executable(da_proj1_no_ansi
                src/main.cpp
                src/ui.cpp
                src/utils.cpp
                src/van.cpp
                src/order.cpp
                src/dataset.cpp src/scenario1.cpp includes/scenario1.hpp includes/scenario3.hpp src/scenario3.cpp includes/scenario2.hpp src/scenario2.cpp)
target_compile_definitions(da_proj1_no_ansi PUBLIC NO_ANSI)

include_directories(da_proj1 includes/)
include_directories(da_proj1_no_ansi includes/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dataset
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started") 
    add_custom_target(Doxygen ALL 
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}" 
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}" 
            COMMENT "Generating API documentation with Doxygen" 
            VERBATIM) 
else(DOXYGEN_FOUND) 
    message("Doxygen needs to be installed to generate the documentation.") 
endif(DOXYGEN_FOUND)
