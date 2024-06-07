cmake_minimum_required(VERSION 3.27)
project(Exam)

set(CMAKE_CXX_STANDARD 20)
enable_testing()

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

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
)

add_executable(SymbolTableTests
        Tests/SymbolTableTests.cpp
)

# Link GTest and GTest_Main to the test executable
target_link_libraries(SymbolTableTests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)
