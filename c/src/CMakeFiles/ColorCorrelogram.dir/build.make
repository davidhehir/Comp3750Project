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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/david/Documents/src/comp3750/project/master/c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/david/Documents/src/comp3750/project/master/c

# Include any dependencies generated for this target.
include src/CMakeFiles/ColorCorrelogram.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/ColorCorrelogram.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/ColorCorrelogram.dir/flags.make

src/CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.o: src/CMakeFiles/ColorCorrelogram.dir/flags.make
src/CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.o: src/ColorCorrelogram.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/david/Documents/src/comp3750/project/master/c/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.o"
	cd /home/david/Documents/src/comp3750/project/master/c/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.o   -c /home/david/Documents/src/comp3750/project/master/c/src/ColorCorrelogram.c

src/CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.i"
	cd /home/david/Documents/src/comp3750/project/master/c/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/david/Documents/src/comp3750/project/master/c/src/ColorCorrelogram.c > CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.i

src/CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.s"
	cd /home/david/Documents/src/comp3750/project/master/c/src && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/david/Documents/src/comp3750/project/master/c/src/ColorCorrelogram.c -o CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.s

src/CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.o.requires:
.PHONY : src/CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.o.requires

src/CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.o.provides: src/CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.o.requires
	$(MAKE) -f src/CMakeFiles/ColorCorrelogram.dir/build.make src/CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.o.provides.build
.PHONY : src/CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.o.provides

src/CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.o.provides.build: src/CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.o
.PHONY : src/CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.o.provides.build

# Object files for target ColorCorrelogram
ColorCorrelogram_OBJECTS = \
"CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.o"

# External object files for target ColorCorrelogram
ColorCorrelogram_EXTERNAL_OBJECTS =

src/libColorCorrelogram.a: src/CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.o
src/libColorCorrelogram.a: src/CMakeFiles/ColorCorrelogram.dir/build.make
src/libColorCorrelogram.a: src/CMakeFiles/ColorCorrelogram.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libColorCorrelogram.a"
	cd /home/david/Documents/src/comp3750/project/master/c/src && $(CMAKE_COMMAND) -P CMakeFiles/ColorCorrelogram.dir/cmake_clean_target.cmake
	cd /home/david/Documents/src/comp3750/project/master/c/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ColorCorrelogram.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/ColorCorrelogram.dir/build: src/libColorCorrelogram.a
.PHONY : src/CMakeFiles/ColorCorrelogram.dir/build

src/CMakeFiles/ColorCorrelogram.dir/requires: src/CMakeFiles/ColorCorrelogram.dir/ColorCorrelogram.c.o.requires
.PHONY : src/CMakeFiles/ColorCorrelogram.dir/requires

src/CMakeFiles/ColorCorrelogram.dir/clean:
	cd /home/david/Documents/src/comp3750/project/master/c/src && $(CMAKE_COMMAND) -P CMakeFiles/ColorCorrelogram.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/ColorCorrelogram.dir/clean

src/CMakeFiles/ColorCorrelogram.dir/depend:
	cd /home/david/Documents/src/comp3750/project/master/c && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/david/Documents/src/comp3750/project/master/c /home/david/Documents/src/comp3750/project/master/c/src /home/david/Documents/src/comp3750/project/master/c /home/david/Documents/src/comp3750/project/master/c/src /home/david/Documents/src/comp3750/project/master/c/src/CMakeFiles/ColorCorrelogram.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/ColorCorrelogram.dir/depend

