cmake_minimum_required(VERSION 3.10)
project(UDPclient C)

set(CMAKE_C_STANDARD 11)

add_executable(UDPclient
        es14client.c
        errlib.h
        errlib.c
        sockwrap.c
        sockwrap.h)
