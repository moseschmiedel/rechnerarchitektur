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

# Include any dependencies generated for this target.
include CMakeFiles/insertion_sort_O3_mini.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/insertion_sort_O3_mini.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/insertion_sort_O3_mini.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/insertion_sort_O3_mini.dir/flags.make

CMakeFiles/insertion_sort_O3_mini.dir/insertion_sort.skeleton_mini.c.o: CMakeFiles/insertion_sort_O3_mini.dir/flags.make
CMakeFiles/insertion_sort_O3_mini.dir/insertion_sort.skeleton_mini.c.o: insertion_sort.skeleton_mini.c
CMakeFiles/insertion_sort_O3_mini.dir/insertion_sort.skeleton_mini.c.o: CMakeFiles/insertion_sort_O3_mini.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mose/projects/rechnerarchitektur/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/insertion_sort_O3_mini.dir/insertion_sort.skeleton_mini.c.o"
	gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/insertion_sort_O3_mini.dir/insertion_sort.skeleton_mini.c.o -MF CMakeFiles/insertion_sort_O3_mini.dir/insertion_sort.skeleton_mini.c.o.d -o CMakeFiles/insertion_sort_O3_mini.dir/insertion_sort.skeleton_mini.c.o -c /home/mose/projects/rechnerarchitektur/bin/insertion_sort.skeleton_mini.c

CMakeFiles/insertion_sort_O3_mini.dir/insertion_sort.skeleton_mini.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/insertion_sort_O3_mini.dir/insertion_sort.skeleton_mini.c.i"
	gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mose/projects/rechnerarchitektur/bin/insertion_sort.skeleton_mini.c > CMakeFiles/insertion_sort_O3_mini.dir/insertion_sort.skeleton_mini.c.i

CMakeFiles/insertion_sort_O3_mini.dir/insertion_sort.skeleton_mini.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/insertion_sort_O3_mini.dir/insertion_sort.skeleton_mini.c.s"
	gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mose/projects/rechnerarchitektur/bin/insertion_sort.skeleton_mini.c -o CMakeFiles/insertion_sort_O3_mini.dir/insertion_sort.skeleton_mini.c.s

# Object files for target insertion_sort_O3_mini
insertion_sort_O3_mini_OBJECTS = \
"CMakeFiles/insertion_sort_O3_mini.dir/insertion_sort.skeleton_mini.c.o"

# External object files for target insertion_sort_O3_mini
insertion_sort_O3_mini_EXTERNAL_OBJECTS =

insertion_sort_O3_mini: CMakeFiles/insertion_sort_O3_mini.dir/insertion_sort.skeleton_mini.c.o
insertion_sort_O3_mini: CMakeFiles/insertion_sort_O3_mini.dir/build.make
insertion_sort_O3_mini: lib_insertion_sort.O3.so
insertion_sort_O3_mini: CMakeFiles/insertion_sort_O3_mini.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mose/projects/rechnerarchitektur/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable insertion_sort_O3_mini"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/insertion_sort_O3_mini.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/insertion_sort_O3_mini.dir/build: insertion_sort_O3_mini
.PHONY : CMakeFiles/insertion_sort_O3_mini.dir/build

CMakeFiles/insertion_sort_O3_mini.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/insertion_sort_O3_mini.dir/cmake_clean.cmake
.PHONY : CMakeFiles/insertion_sort_O3_mini.dir/clean

CMakeFiles/insertion_sort_O3_mini.dir/depend:
	cd /home/mose/projects/rechnerarchitektur/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mose/projects/rechnerarchitektur /home/mose/projects/rechnerarchitektur /home/mose/projects/rechnerarchitektur/bin /home/mose/projects/rechnerarchitektur/bin /home/mose/projects/rechnerarchitektur/bin/CMakeFiles/insertion_sort_O3_mini.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/insertion_sort_O3_mini.dir/depend

