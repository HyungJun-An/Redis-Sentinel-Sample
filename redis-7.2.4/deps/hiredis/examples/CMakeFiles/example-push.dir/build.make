# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anhj/redis-7.2.4/deps/hiredis/examples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anhj/redis-7.2.4/deps/hiredis/examples

# Include any dependencies generated for this target.
include CMakeFiles/example-push.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/example-push.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/example-push.dir/flags.make

CMakeFiles/example-push.dir/example-push.o: CMakeFiles/example-push.dir/flags.make
CMakeFiles/example-push.dir/example-push.o: example-push.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/anhj/redis-7.2.4/deps/hiredis/examples/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/example-push.dir/example-push.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/example-push.dir/example-push.o   -c /home/anhj/redis-7.2.4/deps/hiredis/examples/example-push.c

CMakeFiles/example-push.dir/example-push.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/example-push.dir/example-push.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/anhj/redis-7.2.4/deps/hiredis/examples/example-push.c > CMakeFiles/example-push.dir/example-push.i

CMakeFiles/example-push.dir/example-push.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/example-push.dir/example-push.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/anhj/redis-7.2.4/deps/hiredis/examples/example-push.c -o CMakeFiles/example-push.dir/example-push.s

CMakeFiles/example-push.dir/example-push.o.requires:
.PHONY : CMakeFiles/example-push.dir/example-push.o.requires

CMakeFiles/example-push.dir/example-push.o.provides: CMakeFiles/example-push.dir/example-push.o.requires
	$(MAKE) -f CMakeFiles/example-push.dir/build.make CMakeFiles/example-push.dir/example-push.o.provides.build
.PHONY : CMakeFiles/example-push.dir/example-push.o.provides

CMakeFiles/example-push.dir/example-push.o.provides.build: CMakeFiles/example-push.dir/example-push.o

# Object files for target example-push
example__push_OBJECTS = \
"CMakeFiles/example-push.dir/example-push.o"

# External object files for target example-push
example__push_EXTERNAL_OBJECTS =

example-push: CMakeFiles/example-push.dir/example-push.o
example-push: CMakeFiles/example-push.dir/build.make
example-push: CMakeFiles/example-push.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable example-push"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example-push.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/example-push.dir/build: example-push
.PHONY : CMakeFiles/example-push.dir/build

CMakeFiles/example-push.dir/requires: CMakeFiles/example-push.dir/example-push.o.requires
.PHONY : CMakeFiles/example-push.dir/requires

CMakeFiles/example-push.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/example-push.dir/cmake_clean.cmake
.PHONY : CMakeFiles/example-push.dir/clean

CMakeFiles/example-push.dir/depend:
	cd /home/anhj/redis-7.2.4/deps/hiredis/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anhj/redis-7.2.4/deps/hiredis/examples /home/anhj/redis-7.2.4/deps/hiredis/examples /home/anhj/redis-7.2.4/deps/hiredis/examples /home/anhj/redis-7.2.4/deps/hiredis/examples /home/anhj/redis-7.2.4/deps/hiredis/examples/CMakeFiles/example-push.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/example-push.dir/depend
