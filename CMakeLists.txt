cmake_minimum_required(VERSION 3.26)
project(labwork6_m1keee3)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib)

add_executable(labwork6_m1keee3
        bin/main.cpp
        lib/Hamming.cpp
        lib/Hamming.h
        lib/Pars.cpp
        lib/Pars.h
        lib/filework.h
        lib/filework.cpp)
