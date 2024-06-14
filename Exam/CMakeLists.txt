cmake_minimum_required(VERSION 3.27)
project(Exam)

set(CMAKE_CXX_STANDARD 20)
enable_testing()

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Define common source files
set(COMMON_SRC
    Arrow.cpp
    Arrow.h
    benchmark.h
    benchmark.cpp
    Environment.cpp
    Environment.h
    Molecule.cpp
    Molecule.h
    ParallelSimulation.h
    Reaction.cpp
    Reaction.h
    Simulation.h
    SymbolTable.h
    Vessel.cpp
    Vessel.h
)

add_executable(Exam main.cpp ${COMMON_SRC})

# Define test source files
set(TEST_SRC
    Tests/SymbolTableTests.cpp
    Tests/VesselTests.cpp
)

# Create a test executable for each test source file
foreach(test_src ${TEST_SRC})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src} ${COMMON_SRC})
    target_link_libraries(${test_name} ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)
endforeach()