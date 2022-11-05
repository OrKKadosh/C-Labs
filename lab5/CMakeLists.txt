cmake_minimum_required(VERSION 3.16)
project(Lab5 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Lab5
        LineParser.c
        LineParser.h
        looper.c MyShell.c procs.h procs.c)
