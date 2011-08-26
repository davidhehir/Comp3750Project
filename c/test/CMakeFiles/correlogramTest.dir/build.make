# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/david/Documents/src/comp3750/project/master/c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/david/Documents/src/comp3750/project/master/c

# Include any dependencies generated for this target.
include test/CMakeFiles/correlogramTest.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/correlogramTest.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/correlogramTest.dir/flags.make

test/CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.o: test/CMakeFiles/correlogramTest.dir/flags.make
test/CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.o: test/ColorCorrelogramTest.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/david/Documents/src/comp3750/project/master/c/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object test/CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.o"
	cd /home/david/Documents/src/comp3750/project/master/c/test && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.o   -c /home/david/Documents/src/comp3750/project/master/c/test/ColorCorrelogramTest.c

test/CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.i"
	cd /home/david/Documents/src/comp3750/project/master/c/test && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/david/Documents/src/comp3750/project/master/c/test/ColorCorrelogramTest.c > CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.i

test/CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.s"
	cd /home/david/Documents/src/comp3750/project/master/c/test && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/david/Documents/src/comp3750/project/master/c/test/ColorCorrelogramTest.c -o CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.s

test/CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.o.requires:
.PHONY : test/CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.o.requires

test/CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.o.provides: test/CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.o.requires
	$(MAKE) -f test/CMakeFiles/correlogramTest.dir/build.make test/CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.o.provides.build
.PHONY : test/CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.o.provides

test/CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.o.provides.build: test/CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.o
.PHONY : test/CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.o.provides.build

# Object files for target correlogramTest
correlogramTest_OBJECTS = \
"CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.o"

# External object files for target correlogramTest
correlogramTest_EXTERNAL_OBJECTS =

test/correlogramTest: test/CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.o
test/correlogramTest: src/libColorCorrelogram.a
test/correlogramTest: test/CMakeFiles/correlogramTest.dir/build.make
test/correlogramTest: test/CMakeFiles/correlogramTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable correlogramTest"
	cd /home/david/Documents/src/comp3750/project/master/c/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/correlogramTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/correlogramTest.dir/build: test/correlogramTest
.PHONY : test/CMakeFiles/correlogramTest.dir/build

test/CMakeFiles/correlogramTest.dir/requires: test/CMakeFiles/correlogramTest.dir/ColorCorrelogramTest.c.o.requires
.PHONY : test/CMakeFiles/correlogramTest.dir/requires

test/CMakeFiles/correlogramTest.dir/clean:
	cd /home/david/Documents/src/comp3750/project/master/c/test && $(CMAKE_COMMAND) -P CMakeFiles/correlogramTest.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/correlogramTest.dir/clean

test/CMakeFiles/correlogramTest.dir/depend:
	cd /home/david/Documents/src/comp3750/project/master/c && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/david/Documents/src/comp3750/project/master/c /home/david/Documents/src/comp3750/project/master/c/test /home/david/Documents/src/comp3750/project/master/c /home/david/Documents/src/comp3750/project/master/c/test /home/david/Documents/src/comp3750/project/master/c/test/CMakeFiles/correlogramTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/correlogramTest.dir/depend

