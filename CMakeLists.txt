cmake_minimum_required(VERSION 3.0)
project(shrapnel C)

set(CMAKE_C_STANDARD 99)

add_library(shrapnel
        SE_Stream_Win32.c
        SE_Surface.c
        SE_Draw.c
        SE_Collection.c)