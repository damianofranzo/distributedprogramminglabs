cmake_minimum_required(VERSION 3.10)
project(client1 C)

set(CMAKE_C_STANDARD 11)

add_executable(client1
        client1_main.c
        ../sockwrap.h
        ../sockwrap.c
        ../errlib.c
        ../errlib.h)
