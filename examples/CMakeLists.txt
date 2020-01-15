cmake_minimum_required(VERSION 3.0)
project(shrapnel-example C)

set(CMAKE_C_STANDARD 99)

include_directories(../)

add_executable(shrapnel-example WIN32 example_win32.c)
target_include_directories(shrapnel-example PUBLIC src/)
