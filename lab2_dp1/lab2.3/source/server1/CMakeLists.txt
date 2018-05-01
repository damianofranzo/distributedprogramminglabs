cmake_minimum_required(VERSION 3.10)
project(server1 C)

set(CMAKE_C_STANDARD 11)

add_executable(server1
        server1_main.c
        ../errlib.h
        ../errlib.c
        ../sockwrap.c
        ../sockwrap.h)
