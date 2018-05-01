cmake_minimum_required(VERSION 3.10)
project(UDPserver)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(UDPserver
        errlib.c
        errlib.h
        es14server.c
        sockwrap.c
        sockwrap.h)
