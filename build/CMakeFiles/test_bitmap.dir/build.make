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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/yyc/sylar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yyc/sylar/build

# Include any dependencies generated for this target.
include CMakeFiles/test_bitmap.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_bitmap.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_bitmap.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_bitmap.dir/flags.make

CMakeFiles/test_bitmap.dir/tests/test_bitmap.cc.o: CMakeFiles/test_bitmap.dir/flags.make
CMakeFiles/test_bitmap.dir/tests/test_bitmap.cc.o: ../tests/test_bitmap.cc
CMakeFiles/test_bitmap.dir/tests/test_bitmap.cc.o: CMakeFiles/test_bitmap.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yyc/sylar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_bitmap.dir/tests/test_bitmap.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) -D__FILE__=\"tests/test_bitmap.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_bitmap.dir/tests/test_bitmap.cc.o -MF CMakeFiles/test_bitmap.dir/tests/test_bitmap.cc.o.d -o CMakeFiles/test_bitmap.dir/tests/test_bitmap.cc.o -c /home/yyc/sylar/tests/test_bitmap.cc

CMakeFiles/test_bitmap.dir/tests/test_bitmap.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_bitmap.dir/tests/test_bitmap.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) -D__FILE__=\"tests/test_bitmap.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yyc/sylar/tests/test_bitmap.cc > CMakeFiles/test_bitmap.dir/tests/test_bitmap.cc.i

CMakeFiles/test_bitmap.dir/tests/test_bitmap.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_bitmap.dir/tests/test_bitmap.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) -D__FILE__=\"tests/test_bitmap.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yyc/sylar/tests/test_bitmap.cc -o CMakeFiles/test_bitmap.dir/tests/test_bitmap.cc.s

# Object files for target test_bitmap
test_bitmap_OBJECTS = \
"CMakeFiles/test_bitmap.dir/tests/test_bitmap.cc.o"

# External object files for target test_bitmap
test_bitmap_EXTERNAL_OBJECTS =

../bin/test_bitmap: CMakeFiles/test_bitmap.dir/tests/test_bitmap.cc.o
../bin/test_bitmap: CMakeFiles/test_bitmap.dir/build.make
../bin/test_bitmap: ../lib/libsylar.so
../bin/test_bitmap: /usr/lib/x86_64-linux-gnu/libz.so
../bin/test_bitmap: /usr/lib/x86_64-linux-gnu/libssl.so
../bin/test_bitmap: /usr/lib/x86_64-linux-gnu/libcrypto.so
../bin/test_bitmap: CMakeFiles/test_bitmap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yyc/sylar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/test_bitmap"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_bitmap.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_bitmap.dir/build: ../bin/test_bitmap
.PHONY : CMakeFiles/test_bitmap.dir/build

CMakeFiles/test_bitmap.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_bitmap.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_bitmap.dir/clean

CMakeFiles/test_bitmap.dir/depend:
	cd /home/yyc/sylar/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yyc/sylar /home/yyc/sylar /home/yyc/sylar/build /home/yyc/sylar/build /home/yyc/sylar/build/CMakeFiles/test_bitmap.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_bitmap.dir/depend

