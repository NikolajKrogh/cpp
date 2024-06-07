cmake_minimum_required(VERSION 3.27)
project(Exam)

set(CMAKE_CXX_STANDARD 20)

add_executable(Exam
        Arrow.cpp
        Arrow.h
        Environment.cpp
        Environment.h
        main.cpp
        Molecule.cpp
        Molecule.h
        ParallelSimulation.h
        Reaction.cpp
        Reaction.h
        Simulation.cpp
        Simulation.h
        SymbolTable.h
        Vessel.cpp
        Vessel.h

        Tests/SymbolTableTest.cpp
        Tests/DoctestSetup.cpp
)
