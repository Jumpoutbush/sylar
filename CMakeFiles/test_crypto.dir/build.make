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
CMAKE_BINARY_DIR = /home/yyc/sylar

# Include any dependencies generated for this target.
include CMakeFiles/test_crypto.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_crypto.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_crypto.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_crypto.dir/flags.make

CMakeFiles/test_crypto.dir/tests/test_crypto.cc.o: CMakeFiles/test_crypto.dir/flags.make
CMakeFiles/test_crypto.dir/tests/test_crypto.cc.o: tests/test_crypto.cc
CMakeFiles/test_crypto.dir/tests/test_crypto.cc.o: CMakeFiles/test_crypto.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yyc/sylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_crypto.dir/tests/test_crypto.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"tests/test_crypto.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_crypto.dir/tests/test_crypto.cc.o -MF CMakeFiles/test_crypto.dir/tests/test_crypto.cc.o.d -o CMakeFiles/test_crypto.dir/tests/test_crypto.cc.o -c /home/yyc/sylar/tests/test_crypto.cc

CMakeFiles/test_crypto.dir/tests/test_crypto.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_crypto.dir/tests/test_crypto.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"tests/test_crypto.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yyc/sylar/tests/test_crypto.cc > CMakeFiles/test_crypto.dir/tests/test_crypto.cc.i

CMakeFiles/test_crypto.dir/tests/test_crypto.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_crypto.dir/tests/test_crypto.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"tests/test_crypto.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yyc/sylar/tests/test_crypto.cc -o CMakeFiles/test_crypto.dir/tests/test_crypto.cc.s

# Object files for target test_crypto
test_crypto_OBJECTS = \
"CMakeFiles/test_crypto.dir/tests/test_crypto.cc.o"

# External object files for target test_crypto
test_crypto_EXTERNAL_OBJECTS =

bin/test_crypto: CMakeFiles/test_crypto.dir/tests/test_crypto.cc.o
bin/test_crypto: CMakeFiles/test_crypto.dir/build.make
bin/test_crypto: lib/libsylar.so
bin/test_crypto: /usr/lib/x86_64-linux-gnu/libz.so
bin/test_crypto: /usr/lib/x86_64-linux-gnu/libssl.so
bin/test_crypto: /usr/lib/x86_64-linux-gnu/libcrypto.so
bin/test_crypto: CMakeFiles/test_crypto.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yyc/sylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/test_crypto"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_crypto.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_crypto.dir/build: bin/test_crypto
.PHONY : CMakeFiles/test_crypto.dir/build

CMakeFiles/test_crypto.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_crypto.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_crypto.dir/clean

CMakeFiles/test_crypto.dir/depend:
	cd /home/yyc/sylar && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yyc/sylar /home/yyc/sylar /home/yyc/sylar /home/yyc/sylar /home/yyc/sylar/CMakeFiles/test_crypto.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_crypto.dir/depend

