cmake_minimum_required(VERSION 3.10)

project(cpp_arguments_lib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/logger)

add_library(cpp_arguments_lib STATIC
    arguments.cpp
    arguments.h
    libs/logger/logger.h
    libs/logger/logger.cpp
)

target_compile_options(cpp_arguments_lib PRIVATE -Wall -Wextra)

install(TARGETS cpp_arguments_lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include)

export(TARGETS cpp_arguments_lib FILE cpp_arguments_lib-targets.cmake)
