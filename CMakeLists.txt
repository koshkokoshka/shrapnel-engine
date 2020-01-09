cmake_minimum_required(VERSION 3.0)
project(shrapnel C)

set(CMAKE_C_STANDARD 99)

set(SOURCES
        SE_Surface.c
        SE_Draw.c
        SE_Collection.c
        SE_Math.c)

if(WIN32)
    add_library(shrapnel ${SOURCES} SE_Stream_Win32.c)
    target_link_libraries(shrapnel winmm windowscodecs)
elseif(EMSCRIPTEN)
    add_library(shrapnel ${SOURCES} SE_Stream_Emscripten.c)
else()
    message("Platform not supported")
endif()