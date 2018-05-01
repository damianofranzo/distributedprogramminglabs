cmake_minimum_required(VERSION 3.10)
project(lab2_1 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab2_1
        es21.c
        ../sockwrap.h
        ../sockwrap.c
        ../errlib.c
        ../errlib.h)
