cmake_minimum_required(VERSION 3.15)
project(shrapnel C)

set(CMAKE_C_STANDARD 99)

add_library(shrapnel
        src/SE_Stream_Win32.c
        src/SE_Surface.c
        src/SE_Draw.c
        src/SE_Collection.c)

add_executable(demo WIN32 src/examples/demo.c)
target_include_directories(demo PUBLIC src/)
target_link_libraries(demo shrapnel)
