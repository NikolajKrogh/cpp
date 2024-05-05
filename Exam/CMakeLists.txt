cmake_minimum_required(VERSION 3.27)
project(Exam)

set(CMAKE_CXX_STANDARD 20)

add_executable(Exam main.cpp
        stochastic_simulation_library.cpp
        stochastic_simulation_library.h)
