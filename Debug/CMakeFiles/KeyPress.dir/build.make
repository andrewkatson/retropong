# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/f85/adkatson/Downloads/pong/retropong

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/f85/adkatson/Downloads/pong/retropong/Debug

# Include any dependencies generated for this target.
include CMakeFiles/KeyPress.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/KeyPress.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/KeyPress.dir/flags.make

CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.o: CMakeFiles/KeyPress.dir/flags.make
CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.o: ../bin/KeyPress.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/f85/adkatson/Downloads/pong/retropong/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.o -c /home/f85/adkatson/Downloads/pong/retropong/bin/KeyPress.cpp

CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/f85/adkatson/Downloads/pong/retropong/bin/KeyPress.cpp > CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.i

CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/f85/adkatson/Downloads/pong/retropong/bin/KeyPress.cpp -o CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.s

CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.o.requires:

.PHONY : CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.o.requires

CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.o.provides: CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.o.requires
	$(MAKE) -f CMakeFiles/KeyPress.dir/build.make CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.o.provides.build
.PHONY : CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.o.provides

CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.o.provides.build: CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.o


# Object files for target KeyPress
KeyPress_OBJECTS = \
"CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.o"

# External object files for target KeyPress
KeyPress_EXTERNAL_OBJECTS =

KeyPress: CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.o
KeyPress: CMakeFiles/KeyPress.dir/build.make
KeyPress: /home/f85/adkatson/Downloads/SFML-2.5.0/lib/libsfml-graphics-d.so
KeyPress: /home/f85/adkatson/Downloads/SFML-2.5.0/lib/libsfml-window-d.so
KeyPress: /home/f85/adkatson/Downloads/SFML-2.5.0/lib/libsfml-system-d.so
KeyPress: /home/f85/adkatson/Downloads/SFML-2.5.0/lib/libsfml-audio-d.so
KeyPress: /home/f85/adkatson/Downloads/SFML-2.5.0/lib/libsfml-network-d.so
KeyPress: CMakeFiles/KeyPress.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/f85/adkatson/Downloads/pong/retropong/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable KeyPress"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/KeyPress.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/KeyPress.dir/build: KeyPress

.PHONY : CMakeFiles/KeyPress.dir/build

CMakeFiles/KeyPress.dir/requires: CMakeFiles/KeyPress.dir/bin/KeyPress.cpp.o.requires

.PHONY : CMakeFiles/KeyPress.dir/requires

CMakeFiles/KeyPress.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/KeyPress.dir/cmake_clean.cmake
.PHONY : CMakeFiles/KeyPress.dir/clean

CMakeFiles/KeyPress.dir/depend:
	cd /home/f85/adkatson/Downloads/pong/retropong/Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/f85/adkatson/Downloads/pong/retropong /home/f85/adkatson/Downloads/pong/retropong /home/f85/adkatson/Downloads/pong/retropong/Debug /home/f85/adkatson/Downloads/pong/retropong/Debug /home/f85/adkatson/Downloads/pong/retropong/Debug/CMakeFiles/KeyPress.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/KeyPress.dir/depend

