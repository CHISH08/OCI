# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_SOURCE_DIR = /home/denis/home/OCI/5lab

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/denis/home/OCI/5lab/build

# Include any dependencies generated for this target.
include CMakeFiles/lib2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lib2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lib2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lib2.dir/flags.make

CMakeFiles/lib2.dir/src2/lib2.cpp.o: CMakeFiles/lib2.dir/flags.make
CMakeFiles/lib2.dir/src2/lib2.cpp.o: /home/denis/home/OCI/5lab/src2/lib2.cpp
CMakeFiles/lib2.dir/src2/lib2.cpp.o: CMakeFiles/lib2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/denis/home/OCI/5lab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lib2.dir/src2/lib2.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lib2.dir/src2/lib2.cpp.o -MF CMakeFiles/lib2.dir/src2/lib2.cpp.o.d -o CMakeFiles/lib2.dir/src2/lib2.cpp.o -c /home/denis/home/OCI/5lab/src2/lib2.cpp

CMakeFiles/lib2.dir/src2/lib2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib2.dir/src2/lib2.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/denis/home/OCI/5lab/src2/lib2.cpp > CMakeFiles/lib2.dir/src2/lib2.cpp.i

CMakeFiles/lib2.dir/src2/lib2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib2.dir/src2/lib2.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/denis/home/OCI/5lab/src2/lib2.cpp -o CMakeFiles/lib2.dir/src2/lib2.cpp.s

# Object files for target lib2
lib2_OBJECTS = \
"CMakeFiles/lib2.dir/src2/lib2.cpp.o"

# External object files for target lib2
lib2_EXTERNAL_OBJECTS =

liblib2.so: CMakeFiles/lib2.dir/src2/lib2.cpp.o
liblib2.so: CMakeFiles/lib2.dir/build.make
liblib2.so: CMakeFiles/lib2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/denis/home/OCI/5lab/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library liblib2.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lib2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lib2.dir/build: liblib2.so
.PHONY : CMakeFiles/lib2.dir/build

CMakeFiles/lib2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lib2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lib2.dir/clean

CMakeFiles/lib2.dir/depend:
	cd /home/denis/home/OCI/5lab/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/denis/home/OCI/5lab /home/denis/home/OCI/5lab /home/denis/home/OCI/5lab/build /home/denis/home/OCI/5lab/build /home/denis/home/OCI/5lab/build/CMakeFiles/lib2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lib2.dir/depend

