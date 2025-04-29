# CMake
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
endif()

# Python.h includes
execute_process(
    COMMAND python3-config --includes
    OUTPUT_VARIABLE PYTHON_INCLUDES
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# CXX
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Werror -Wall -Wpedantic -D_THREAD_SAFE -fms-extensions -Wno-nested-anon-types -Wno-gnu-anonymous-struct ${PYTHON_INCLUDES} -Iext/pybind11/include")

# Project
project(Glacier VERSION 1.0 LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if(APPLE)
    add_definitions(-Wno-deprecated-declarations)
endif()

# pybind11
add_subdirectory("ext/pybind11")

# Includes and libraries
set(INCLUDE_DIRS "src" "ext")

# Include search directories
include_directories(${INCLUDE_DIRS})

# Subdirectories
add_subdirectory(src)
