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
include CMakeFiles/echo_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/echo_server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/echo_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/echo_server.dir/flags.make

CMakeFiles/echo_server.dir/examples/echo_server.cc.o: CMakeFiles/echo_server.dir/flags.make
CMakeFiles/echo_server.dir/examples/echo_server.cc.o: examples/echo_server.cc
CMakeFiles/echo_server.dir/examples/echo_server.cc.o: CMakeFiles/echo_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yyc/sylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/echo_server.dir/examples/echo_server.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"examples/echo_server.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/echo_server.dir/examples/echo_server.cc.o -MF CMakeFiles/echo_server.dir/examples/echo_server.cc.o.d -o CMakeFiles/echo_server.dir/examples/echo_server.cc.o -c /home/yyc/sylar/examples/echo_server.cc

CMakeFiles/echo_server.dir/examples/echo_server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_server.dir/examples/echo_server.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"examples/echo_server.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yyc/sylar/examples/echo_server.cc > CMakeFiles/echo_server.dir/examples/echo_server.cc.i

CMakeFiles/echo_server.dir/examples/echo_server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_server.dir/examples/echo_server.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"examples/echo_server.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yyc/sylar/examples/echo_server.cc -o CMakeFiles/echo_server.dir/examples/echo_server.cc.s

# Object files for target echo_server
echo_server_OBJECTS = \
"CMakeFiles/echo_server.dir/examples/echo_server.cc.o"

# External object files for target echo_server
echo_server_EXTERNAL_OBJECTS =

bin/echo_server: CMakeFiles/echo_server.dir/examples/echo_server.cc.o
bin/echo_server: CMakeFiles/echo_server.dir/build.make
bin/echo_server: lib/libsylar.so
bin/echo_server: /usr/lib/x86_64-linux-gnu/libz.so
bin/echo_server: /usr/lib/x86_64-linux-gnu/libssl.so
bin/echo_server: /usr/lib/x86_64-linux-gnu/libcrypto.so
bin/echo_server: CMakeFiles/echo_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yyc/sylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/echo_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/echo_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/echo_server.dir/build: bin/echo_server
.PHONY : CMakeFiles/echo_server.dir/build

CMakeFiles/echo_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/echo_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/echo_server.dir/clean

CMakeFiles/echo_server.dir/depend:
	cd /home/yyc/sylar && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yyc/sylar /home/yyc/sylar /home/yyc/sylar /home/yyc/sylar /home/yyc/sylar/CMakeFiles/echo_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/echo_server.dir/depend

