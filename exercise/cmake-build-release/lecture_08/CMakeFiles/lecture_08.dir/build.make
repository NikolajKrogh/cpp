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
include lecture_08/CMakeFiles/lecture_08.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lecture_08/CMakeFiles/lecture_08.dir/compiler_depend.make

# Include the progress variables for this target.
include lecture_08/CMakeFiles/lecture_08.dir/progress.make

# Include the compile flags for this target's objects.
include lecture_08/CMakeFiles/lecture_08.dir/flags.make

lecture_08/CMakeFiles/lecture_08.dir/lecture_08.cpp.o: lecture_08/CMakeFiles/lecture_08.dir/flags.make
lecture_08/CMakeFiles/lecture_08.dir/lecture_08.cpp.o: ../lecture_08/lecture_08.cpp
lecture_08/CMakeFiles/lecture_08.dir/lecture_08.cpp.o: lecture_08/CMakeFiles/lecture_08.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lecture_08/CMakeFiles/lecture_08.dir/lecture_08.cpp.o"
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/lecture_08 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lecture_08/CMakeFiles/lecture_08.dir/lecture_08.cpp.o -MF CMakeFiles/lecture_08.dir/lecture_08.cpp.o.d -o CMakeFiles/lecture_08.dir/lecture_08.cpp.o -c /mnt/c/Users/nikol/Documents/GitHub/cpp/lecture_08/lecture_08.cpp

lecture_08/CMakeFiles/lecture_08.dir/lecture_08.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lecture_08.dir/lecture_08.cpp.i"
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/lecture_08 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/nikol/Documents/GitHub/cpp/lecture_08/lecture_08.cpp > CMakeFiles/lecture_08.dir/lecture_08.cpp.i

lecture_08/CMakeFiles/lecture_08.dir/lecture_08.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lecture_08.dir/lecture_08.cpp.s"
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/lecture_08 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/nikol/Documents/GitHub/cpp/lecture_08/lecture_08.cpp -o CMakeFiles/lecture_08.dir/lecture_08.cpp.s

# Object files for target lecture_08
lecture_08_OBJECTS = \
"CMakeFiles/lecture_08.dir/lecture_08.cpp.o"

# External object files for target lecture_08
lecture_08_EXTERNAL_OBJECTS =

lecture_08/lecture_08: lecture_08/CMakeFiles/lecture_08.dir/lecture_08.cpp.o
lecture_08/lecture_08: lecture_08/CMakeFiles/lecture_08.dir/build.make
lecture_08/lecture_08: lecture_08/CMakeFiles/lecture_08.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lecture_08"
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/lecture_08 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lecture_08.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lecture_08/CMakeFiles/lecture_08.dir/build: lecture_08/lecture_08
.PHONY : lecture_08/CMakeFiles/lecture_08.dir/build

lecture_08/CMakeFiles/lecture_08.dir/clean:
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/lecture_08 && $(CMAKE_COMMAND) -P CMakeFiles/lecture_08.dir/cmake_clean.cmake
.PHONY : lecture_08/CMakeFiles/lecture_08.dir/clean

lecture_08/CMakeFiles/lecture_08.dir/depend:
	cd /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/nikol/Documents/GitHub/cpp /mnt/c/Users/nikol/Documents/GitHub/cpp/lecture_08 /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/lecture_08 /mnt/c/Users/nikol/Documents/GitHub/cpp/cmake-build-release/lecture_08/CMakeFiles/lecture_08.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lecture_08/CMakeFiles/lecture_08.dir/depend

