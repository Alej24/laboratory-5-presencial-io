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
CMAKE_SOURCE_DIR = "/home/ale159/Laboratory 5 presencial team"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/ale159/Laboratory 5 presencial team/build"

# Include any dependencies generated for this target.
include CMakeFiles/lab5io.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lab5io.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lab5io.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab5io.dir/flags.make

CMakeFiles/lab5io.dir/src/lab5io.c.o: CMakeFiles/lab5io.dir/flags.make
CMakeFiles/lab5io.dir/src/lab5io.c.o: ../src/lab5io.c
CMakeFiles/lab5io.dir/src/lab5io.c.o: CMakeFiles/lab5io.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/ale159/Laboratory 5 presencial team/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lab5io.dir/src/lab5io.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lab5io.dir/src/lab5io.c.o -MF CMakeFiles/lab5io.dir/src/lab5io.c.o.d -o CMakeFiles/lab5io.dir/src/lab5io.c.o -c "/home/ale159/Laboratory 5 presencial team/src/lab5io.c"

CMakeFiles/lab5io.dir/src/lab5io.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab5io.dir/src/lab5io.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/ale159/Laboratory 5 presencial team/src/lab5io.c" > CMakeFiles/lab5io.dir/src/lab5io.c.i

CMakeFiles/lab5io.dir/src/lab5io.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab5io.dir/src/lab5io.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/ale159/Laboratory 5 presencial team/src/lab5io.c" -o CMakeFiles/lab5io.dir/src/lab5io.c.s

CMakeFiles/lab5io.dir/src/main.c.o: CMakeFiles/lab5io.dir/flags.make
CMakeFiles/lab5io.dir/src/main.c.o: ../src/main.c
CMakeFiles/lab5io.dir/src/main.c.o: CMakeFiles/lab5io.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/ale159/Laboratory 5 presencial team/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/lab5io.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lab5io.dir/src/main.c.o -MF CMakeFiles/lab5io.dir/src/main.c.o.d -o CMakeFiles/lab5io.dir/src/main.c.o -c "/home/ale159/Laboratory 5 presencial team/src/main.c"

CMakeFiles/lab5io.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab5io.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/ale159/Laboratory 5 presencial team/src/main.c" > CMakeFiles/lab5io.dir/src/main.c.i

CMakeFiles/lab5io.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab5io.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/ale159/Laboratory 5 presencial team/src/main.c" -o CMakeFiles/lab5io.dir/src/main.c.s

# Object files for target lab5io
lab5io_OBJECTS = \
"CMakeFiles/lab5io.dir/src/lab5io.c.o" \
"CMakeFiles/lab5io.dir/src/main.c.o"

# External object files for target lab5io
lab5io_EXTERNAL_OBJECTS =

lab5io: CMakeFiles/lab5io.dir/src/lab5io.c.o
lab5io: CMakeFiles/lab5io.dir/src/main.c.o
lab5io: CMakeFiles/lab5io.dir/build.make
lab5io: CMakeFiles/lab5io.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/ale159/Laboratory 5 presencial team/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable lab5io"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab5io.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab5io.dir/build: lab5io
.PHONY : CMakeFiles/lab5io.dir/build

CMakeFiles/lab5io.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab5io.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab5io.dir/clean

CMakeFiles/lab5io.dir/depend:
	cd "/home/ale159/Laboratory 5 presencial team/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/ale159/Laboratory 5 presencial team" "/home/ale159/Laboratory 5 presencial team" "/home/ale159/Laboratory 5 presencial team/build" "/home/ale159/Laboratory 5 presencial team/build" "/home/ale159/Laboratory 5 presencial team/build/CMakeFiles/lab5io.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/lab5io.dir/depend

