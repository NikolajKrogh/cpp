cmake_minimum_required(VERSION 3.27)
project(exam)

set(CMAKE_CXX_STANDARD 20)

add_executable(exam main.cpp
        stochastic_simulation_library.cpp
        stochastic_simulation_library.h)
