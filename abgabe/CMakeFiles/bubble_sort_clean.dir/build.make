# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_SOURCE_DIR = /home/mose/projects/rechnerarchitektur

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mose/projects/rechnerarchitektur/bin

# Utility rule file for bubble_sort_clean.

# Include any custom commands dependencies for this target.
include CMakeFiles/bubble_sort_clean.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bubble_sort_clean.dir/progress.make

CMakeFiles/bubble_sort_clean:
	rm /home/mose/projects/rechnerarchitektur/bin/bubble_sort.ripes.c.in
	rm /home/mose/projects/rechnerarchitektur/bin/bubble_sort.skeleton.c.in
	rm /home/mose/projects/rechnerarchitektur/bin/bubble_sort.skeleton.c
	rm /home/mose/projects/rechnerarchitektur/bin/bubble_sort.skeleton_mini.c

bubble_sort_clean: CMakeFiles/bubble_sort_clean
bubble_sort_clean: CMakeFiles/bubble_sort_clean.dir/build.make
.PHONY : bubble_sort_clean

# Rule to build all files generated by this target.
CMakeFiles/bubble_sort_clean.dir/build: bubble_sort_clean
.PHONY : CMakeFiles/bubble_sort_clean.dir/build

CMakeFiles/bubble_sort_clean.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bubble_sort_clean.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bubble_sort_clean.dir/clean

CMakeFiles/bubble_sort_clean.dir/depend:
	cd /home/mose/projects/rechnerarchitektur/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mose/projects/rechnerarchitektur /home/mose/projects/rechnerarchitektur /home/mose/projects/rechnerarchitektur/bin /home/mose/projects/rechnerarchitektur/bin /home/mose/projects/rechnerarchitektur/bin/CMakeFiles/bubble_sort_clean.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bubble_sort_clean.dir/depend
