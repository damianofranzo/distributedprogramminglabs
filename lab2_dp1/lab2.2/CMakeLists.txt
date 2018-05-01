cmake_minimum_required(VERSION 3.10)
project(lab2_2 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab2_2
        es22.c
        ../sockwrap.c
        ../sockwrap.h
        ../errlib.h
        ../errlib.c
        circbuff.c
        circbuff.h)
