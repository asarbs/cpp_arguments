cmake_minimum_required(VERSION 3.10)

project(cpp_arguments_lib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_COMPILER clang++-18)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(
    -g
    -Wall 
    -pedantic
    -std=c++20
    -fpermissive
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/logger)

add_library(cpp_arguments_lib STATIC
    arguments.cpp
    arguments.h
)

target_compile_options(cpp_arguments_lib PRIVATE -Wall)

install(TARGETS cpp_arguments_lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include)

export(TARGETS cpp_arguments_lib FILE cpp_arguments_lib-targets.cmake)
