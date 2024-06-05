cmake_minimum_required(VERSION 3.27)
project(Exam)

set(CMAKE_CXX_STANDARD 20)

add_executable(Exam main.cpp
        ParallelSimulation.h
        Simulation.cpp
        Simulation.h
        Vessel.cpp
        Vessel.h
        SymbolTable.h
        Arrow.cpp
        Arrow.h
        Environment.cpp
        Environment.h
        Reaction.cpp
        Reaction.h
        Molecule.cpp
        Molecule.h
)
