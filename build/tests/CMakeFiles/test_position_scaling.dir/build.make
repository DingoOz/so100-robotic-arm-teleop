# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/dingo/Programming/so100-robotic-arm-teleop

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dingo/Programming/so100-robotic-arm-teleop/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_position_scaling.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/test_position_scaling.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_position_scaling.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_position_scaling.dir/flags.make

tests/CMakeFiles/test_position_scaling.dir/test_position_scaling.cpp.o: tests/CMakeFiles/test_position_scaling.dir/flags.make
tests/CMakeFiles/test_position_scaling.dir/test_position_scaling.cpp.o: /home/dingo/Programming/so100-robotic-arm-teleop/tests/test_position_scaling.cpp
tests/CMakeFiles/test_position_scaling.dir/test_position_scaling.cpp.o: tests/CMakeFiles/test_position_scaling.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dingo/Programming/so100-robotic-arm-teleop/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/test_position_scaling.dir/test_position_scaling.cpp.o"
	cd /home/dingo/Programming/so100-robotic-arm-teleop/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/test_position_scaling.dir/test_position_scaling.cpp.o -MF CMakeFiles/test_position_scaling.dir/test_position_scaling.cpp.o.d -o CMakeFiles/test_position_scaling.dir/test_position_scaling.cpp.o -c /home/dingo/Programming/so100-robotic-arm-teleop/tests/test_position_scaling.cpp

tests/CMakeFiles/test_position_scaling.dir/test_position_scaling.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_position_scaling.dir/test_position_scaling.cpp.i"
	cd /home/dingo/Programming/so100-robotic-arm-teleop/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dingo/Programming/so100-robotic-arm-teleop/tests/test_position_scaling.cpp > CMakeFiles/test_position_scaling.dir/test_position_scaling.cpp.i

tests/CMakeFiles/test_position_scaling.dir/test_position_scaling.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_position_scaling.dir/test_position_scaling.cpp.s"
	cd /home/dingo/Programming/so100-robotic-arm-teleop/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dingo/Programming/so100-robotic-arm-teleop/tests/test_position_scaling.cpp -o CMakeFiles/test_position_scaling.dir/test_position_scaling.cpp.s

# Object files for target test_position_scaling
test_position_scaling_OBJECTS = \
"CMakeFiles/test_position_scaling.dir/test_position_scaling.cpp.o"

# External object files for target test_position_scaling
test_position_scaling_EXTERNAL_OBJECTS = \
"/home/dingo/Programming/so100-robotic-arm-teleop/build/tests/CMakeFiles/test_main.dir/test_main.cpp.o"

tests/test_position_scaling: tests/CMakeFiles/test_position_scaling.dir/test_position_scaling.cpp.o
tests/test_position_scaling: tests/CMakeFiles/test_main.dir/test_main.cpp.o
tests/test_position_scaling: tests/CMakeFiles/test_position_scaling.dir/build.make
tests/test_position_scaling: _deps/catch2-build/src/libCatch2Maind.a
tests/test_position_scaling: _deps/catch2-build/src/libCatch2d.a
tests/test_position_scaling: tests/CMakeFiles/test_position_scaling.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/dingo/Programming/so100-robotic-arm-teleop/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_position_scaling"
	cd /home/dingo/Programming/so100-robotic-arm-teleop/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_position_scaling.dir/link.txt --verbose=$(VERBOSE)
	cd /home/dingo/Programming/so100-robotic-arm-teleop/build/tests && /usr/bin/cmake -D TEST_TARGET=test_position_scaling -D TEST_EXECUTABLE=/home/dingo/Programming/so100-robotic-arm-teleop/build/tests/test_position_scaling -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/dingo/Programming/so100-robotic-arm-teleop/build/tests -D TEST_SPEC= -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_LIST=test_position_scaling_TESTS -D TEST_REPORTER= -D TEST_OUTPUT_DIR= -D TEST_OUTPUT_PREFIX= -D TEST_OUTPUT_SUFFIX= -D TEST_DL_PATHS= -D CTEST_FILE=/home/dingo/Programming/so100-robotic-arm-teleop/build/tests/test_position_scaling-b12d07c_tests.cmake -P /home/dingo/Programming/so100-robotic-arm-teleop/build/_deps/catch2-src/extras/CatchAddTests.cmake

# Rule to build all files generated by this target.
tests/CMakeFiles/test_position_scaling.dir/build: tests/test_position_scaling
.PHONY : tests/CMakeFiles/test_position_scaling.dir/build

tests/CMakeFiles/test_position_scaling.dir/clean:
	cd /home/dingo/Programming/so100-robotic-arm-teleop/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_position_scaling.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_position_scaling.dir/clean

tests/CMakeFiles/test_position_scaling.dir/depend:
	cd /home/dingo/Programming/so100-robotic-arm-teleop/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dingo/Programming/so100-robotic-arm-teleop /home/dingo/Programming/so100-robotic-arm-teleop/tests /home/dingo/Programming/so100-robotic-arm-teleop/build /home/dingo/Programming/so100-robotic-arm-teleop/build/tests /home/dingo/Programming/so100-robotic-arm-teleop/build/tests/CMakeFiles/test_position_scaling.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/CMakeFiles/test_position_scaling.dir/depend

