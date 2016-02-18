cmake_minimum_required(VERSION 3.3)
project(hw3_sol)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    hw3.c
    shell.c
    shell.h)

add_executable(hw3_sol ${SOURCE_FILES})