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
CMAKE_SOURCE_DIR = /home/yyc/sylar/chat_room

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yyc/sylar/chat_room/build

# Include any dependencies generated for this target.
include sylar/CMakeFiles/test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include sylar/CMakeFiles/test.dir/compiler_depend.make

# Include the progress variables for this target.
include sylar/CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include sylar/CMakeFiles/test.dir/flags.make

sylar/CMakeFiles/test.dir/tests/test.cc.o: sylar/CMakeFiles/test.dir/flags.make
sylar/CMakeFiles/test.dir/tests/test.cc.o: ../sylar/tests/test.cc
sylar/CMakeFiles/test.dir/tests/test.cc.o: sylar/CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yyc/sylar/chat_room/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object sylar/CMakeFiles/test.dir/tests/test.cc.o"
	cd /home/yyc/sylar/chat_room/build/sylar && /usr/bin/g++ $(CXX_DEFINES) -D__FILE__=\"tests/test.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT sylar/CMakeFiles/test.dir/tests/test.cc.o -MF CMakeFiles/test.dir/tests/test.cc.o.d -o CMakeFiles/test.dir/tests/test.cc.o -c /home/yyc/sylar/chat_room/sylar/tests/test.cc

sylar/CMakeFiles/test.dir/tests/test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/tests/test.cc.i"
	cd /home/yyc/sylar/chat_room/build/sylar && /usr/bin/g++ $(CXX_DEFINES) -D__FILE__=\"tests/test.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yyc/sylar/chat_room/sylar/tests/test.cc > CMakeFiles/test.dir/tests/test.cc.i

sylar/CMakeFiles/test.dir/tests/test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/tests/test.cc.s"
	cd /home/yyc/sylar/chat_room/build/sylar && /usr/bin/g++ $(CXX_DEFINES) -D__FILE__=\"tests/test.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yyc/sylar/chat_room/sylar/tests/test.cc -o CMakeFiles/test.dir/tests/test.cc.s

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/tests/test.cc.o"

# External object files for target test
test_EXTERNAL_OBJECTS =

../sylar/bin/test: sylar/CMakeFiles/test.dir/tests/test.cc.o
../sylar/bin/test: sylar/CMakeFiles/test.dir/build.make
../sylar/bin/test: ../sylar/lib/libsylar.so
../sylar/bin/test: /usr/lib/x86_64-linux-gnu/libz.so
../sylar/bin/test: /usr/lib/x86_64-linux-gnu/libssl.so
../sylar/bin/test: /usr/lib/x86_64-linux-gnu/libcrypto.so
../sylar/bin/test: sylar/CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yyc/sylar/chat_room/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../sylar/bin/test"
	cd /home/yyc/sylar/chat_room/build/sylar && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sylar/CMakeFiles/test.dir/build: ../sylar/bin/test
.PHONY : sylar/CMakeFiles/test.dir/build

sylar/CMakeFiles/test.dir/clean:
	cd /home/yyc/sylar/chat_room/build/sylar && $(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : sylar/CMakeFiles/test.dir/clean

sylar/CMakeFiles/test.dir/depend:
	cd /home/yyc/sylar/chat_room/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yyc/sylar/chat_room /home/yyc/sylar/chat_room/sylar /home/yyc/sylar/chat_room/build /home/yyc/sylar/chat_room/build/sylar /home/yyc/sylar/chat_room/build/sylar/CMakeFiles/test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sylar/CMakeFiles/test.dir/depend

