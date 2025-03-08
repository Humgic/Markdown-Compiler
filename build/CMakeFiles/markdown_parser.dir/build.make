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
CMAKE_SOURCE_DIR = /home/wsy/markdown_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wsy/markdown_cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/markdown_parser.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/markdown_parser.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/markdown_parser.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/markdown_parser.dir/flags.make

CMakeFiles/markdown_parser.dir/src/parser/parser.cpp.o: CMakeFiles/markdown_parser.dir/flags.make
CMakeFiles/markdown_parser.dir/src/parser/parser.cpp.o: /home/wsy/markdown_cpp/src/parser/parser.cpp
CMakeFiles/markdown_parser.dir/src/parser/parser.cpp.o: CMakeFiles/markdown_parser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/wsy/markdown_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/markdown_parser.dir/src/parser/parser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/markdown_parser.dir/src/parser/parser.cpp.o -MF CMakeFiles/markdown_parser.dir/src/parser/parser.cpp.o.d -o CMakeFiles/markdown_parser.dir/src/parser/parser.cpp.o -c /home/wsy/markdown_cpp/src/parser/parser.cpp

CMakeFiles/markdown_parser.dir/src/parser/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/markdown_parser.dir/src/parser/parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wsy/markdown_cpp/src/parser/parser.cpp > CMakeFiles/markdown_parser.dir/src/parser/parser.cpp.i

CMakeFiles/markdown_parser.dir/src/parser/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/markdown_parser.dir/src/parser/parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wsy/markdown_cpp/src/parser/parser.cpp -o CMakeFiles/markdown_parser.dir/src/parser/parser.cpp.s

# Object files for target markdown_parser
markdown_parser_OBJECTS = \
"CMakeFiles/markdown_parser.dir/src/parser/parser.cpp.o"

# External object files for target markdown_parser
markdown_parser_EXTERNAL_OBJECTS =

lib/libmarkdown_parser.a: CMakeFiles/markdown_parser.dir/src/parser/parser.cpp.o
lib/libmarkdown_parser.a: CMakeFiles/markdown_parser.dir/build.make
lib/libmarkdown_parser.a: CMakeFiles/markdown_parser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/wsy/markdown_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library lib/libmarkdown_parser.a"
	$(CMAKE_COMMAND) -P CMakeFiles/markdown_parser.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/markdown_parser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/markdown_parser.dir/build: lib/libmarkdown_parser.a
.PHONY : CMakeFiles/markdown_parser.dir/build

CMakeFiles/markdown_parser.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/markdown_parser.dir/cmake_clean.cmake
.PHONY : CMakeFiles/markdown_parser.dir/clean

CMakeFiles/markdown_parser.dir/depend:
	cd /home/wsy/markdown_cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wsy/markdown_cpp /home/wsy/markdown_cpp /home/wsy/markdown_cpp/build /home/wsy/markdown_cpp/build /home/wsy/markdown_cpp/build/CMakeFiles/markdown_parser.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/markdown_parser.dir/depend

