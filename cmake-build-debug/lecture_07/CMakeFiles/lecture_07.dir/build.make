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
CMAKE_BINARY_DIR = /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-debug

# Include any dependencies generated for this target.
include lecture_07/CMakeFiles/lecture_07.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lecture_07/CMakeFiles/lecture_07.dir/compiler_depend.make

# Include the progress variables for this target.
include lecture_07/CMakeFiles/lecture_07.dir/progress.make

# Include the compile flags for this target's objects.
include lecture_07/CMakeFiles/lecture_07.dir/flags.make

lecture_07/CMakeFiles/lecture_07.dir/lecture_07.cpp.o: lecture_07/CMakeFiles/lecture_07.dir/flags.make
lecture_07/CMakeFiles/lecture_07.dir/lecture_07.cpp.o: ../lecture_07/lecture_07.cpp
lecture_07/CMakeFiles/lecture_07.dir/lecture_07.cpp.o: lecture_07/CMakeFiles/lecture_07.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lecture_07/CMakeFiles/lecture_07.dir/lecture_07.cpp.o"
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-debug/lecture_07 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lecture_07/CMakeFiles/lecture_07.dir/lecture_07.cpp.o -MF CMakeFiles/lecture_07.dir/lecture_07.cpp.o.d -o CMakeFiles/lecture_07.dir/lecture_07.cpp.o -c /mnt/c/Users/nikol/Documents/GitHub/cpp/lecture_07/lecture_07.cpp

lecture_07/CMakeFiles/lecture_07.dir/lecture_07.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lecture_07.dir/lecture_07.cpp.i"
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-debug/lecture_07 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/nikol/Documents/GitHub/cpp/lecture_07/lecture_07.cpp > CMakeFiles/lecture_07.dir/lecture_07.cpp.i

lecture_07/CMakeFiles/lecture_07.dir/lecture_07.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lecture_07.dir/lecture_07.cpp.s"
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-debug/lecture_07 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/nikol/Documents/GitHub/cpp/lecture_07/lecture_07.cpp -o CMakeFiles/lecture_07.dir/lecture_07.cpp.s

# Object files for target lecture_07
lecture_07_OBJECTS = \
"CMakeFiles/lecture_07.dir/lecture_07.cpp.o"

# External object files for target lecture_07
lecture_07_EXTERNAL_OBJECTS =

lecture_07/lecture_07: lecture_07/CMakeFiles/lecture_07.dir/lecture_07.cpp.o
lecture_07/lecture_07: lecture_07/CMakeFiles/lecture_07.dir/build.make
lecture_07/lecture_07: lecture_07/CMakeFiles/lecture_07.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lecture_07"
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-debug/lecture_07 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lecture_07.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lecture_07/CMakeFiles/lecture_07.dir/build: lecture_07/lecture_07
.PHONY : lecture_07/CMakeFiles/lecture_07.dir/build

lecture_07/CMakeFiles/lecture_07.dir/clean:
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-debug/lecture_07 && $(CMAKE_COMMAND) -P CMakeFiles/lecture_07.dir/cmake_clean.cmake
.PHONY : lecture_07/CMakeFiles/lecture_07.dir/clean

lecture_07/CMakeFiles/lecture_07.dir/depend:
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/nikol/Documents/GitHub/cpp /mnt/c/Users/nikol/Documents/GitHub/cpp/lecture_07 /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-debug /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-debug/lecture_07 /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-debug/lecture_07/CMakeFiles/lecture_07.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lecture_07/CMakeFiles/lecture_07.dir/depend

