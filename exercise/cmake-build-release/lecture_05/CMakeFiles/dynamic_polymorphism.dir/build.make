# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/nikol/Documents/GitHub/cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release

# Include any dependencies generated for this target.
include lecture_05/CMakeFiles/dynamic_polymorphism.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lecture_05/CMakeFiles/dynamic_polymorphism.dir/compiler_depend.make

# Include the progress variables for this target.
include lecture_05/CMakeFiles/dynamic_polymorphism.dir/progress.make

# Include the compile flags for this target's objects.
include lecture_05/CMakeFiles/dynamic_polymorphism.dir/flags.make

lecture_05/CMakeFiles/dynamic_polymorphism.dir/dynamic_polymorphism.cpp.o: lecture_05/CMakeFiles/dynamic_polymorphism.dir/flags.make
lecture_05/CMakeFiles/dynamic_polymorphism.dir/dynamic_polymorphism.cpp.o: ../lecture_05/dynamic_polymorphism.cpp
lecture_05/CMakeFiles/dynamic_polymorphism.dir/dynamic_polymorphism.cpp.o: lecture_05/CMakeFiles/dynamic_polymorphism.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lecture_05/CMakeFiles/dynamic_polymorphism.dir/dynamic_polymorphism.cpp.o"
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/lecture_05 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lecture_05/CMakeFiles/dynamic_polymorphism.dir/dynamic_polymorphism.cpp.o -MF CMakeFiles/dynamic_polymorphism.dir/dynamic_polymorphism.cpp.o.d -o CMakeFiles/dynamic_polymorphism.dir/dynamic_polymorphism.cpp.o -c /mnt/c/Users/nikol/Documents/GitHub/cpp/lecture_05/dynamic_polymorphism.cpp

lecture_05/CMakeFiles/dynamic_polymorphism.dir/dynamic_polymorphism.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dynamic_polymorphism.dir/dynamic_polymorphism.cpp.i"
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/lecture_05 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/nikol/Documents/GitHub/cpp/lecture_05/dynamic_polymorphism.cpp > CMakeFiles/dynamic_polymorphism.dir/dynamic_polymorphism.cpp.i

lecture_05/CMakeFiles/dynamic_polymorphism.dir/dynamic_polymorphism.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dynamic_polymorphism.dir/dynamic_polymorphism.cpp.s"
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/lecture_05 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/nikol/Documents/GitHub/cpp/lecture_05/dynamic_polymorphism.cpp -o CMakeFiles/dynamic_polymorphism.dir/dynamic_polymorphism.cpp.s

# Object files for target dynamic_polymorphism
dynamic_polymorphism_OBJECTS = \
"CMakeFiles/dynamic_polymorphism.dir/dynamic_polymorphism.cpp.o"

# External object files for target dynamic_polymorphism
dynamic_polymorphism_EXTERNAL_OBJECTS =

lecture_05/dynamic_polymorphism: lecture_05/CMakeFiles/dynamic_polymorphism.dir/dynamic_polymorphism.cpp.o
lecture_05/dynamic_polymorphism: lecture_05/CMakeFiles/dynamic_polymorphism.dir/build.make
lecture_05/dynamic_polymorphism: lecture_05/CMakeFiles/dynamic_polymorphism.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable dynamic_polymorphism"
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/lecture_05 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dynamic_polymorphism.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lecture_05/CMakeFiles/dynamic_polymorphism.dir/build: lecture_05/dynamic_polymorphism
.PHONY : lecture_05/CMakeFiles/dynamic_polymorphism.dir/build

lecture_05/CMakeFiles/dynamic_polymorphism.dir/clean:
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/lecture_05 && $(CMAKE_COMMAND) -P CMakeFiles/dynamic_polymorphism.dir/cmake_clean.cmake
.PHONY : lecture_05/CMakeFiles/dynamic_polymorphism.dir/clean

lecture_05/CMakeFiles/dynamic_polymorphism.dir/depend:
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/nikol/Documents/GitHub/cpp /mnt/c/Users/nikol/Documents/GitHub/cpp/lecture_05 /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/lecture_05 /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/lecture_05/CMakeFiles/dynamic_polymorphism.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lecture_05/CMakeFiles/dynamic_polymorphism.dir/depend

