# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/solalgaillard/Downloads/Solal Gaillard - 13406890 - Série 3 - Projet Final/SOM_C"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/solalgaillard/Downloads/Solal Gaillard - 13406890 - Série 3 - Projet Final/SOM_C/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/SOM_C.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SOM_C.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SOM_C.dir/flags.make

CMakeFiles/SOM_C.dir/main.c.o: CMakeFiles/SOM_C.dir/flags.make
CMakeFiles/SOM_C.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/solalgaillard/Downloads/Solal Gaillard - 13406890 - Série 3 - Projet Final/SOM_C/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SOM_C.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SOM_C.dir/main.c.o   -c "/Users/solalgaillard/Downloads/Solal Gaillard - 13406890 - Série 3 - Projet Final/SOM_C/main.c"

CMakeFiles/SOM_C.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SOM_C.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/solalgaillard/Downloads/Solal Gaillard - 13406890 - Série 3 - Projet Final/SOM_C/main.c" > CMakeFiles/SOM_C.dir/main.c.i

CMakeFiles/SOM_C.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SOM_C.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/solalgaillard/Downloads/Solal Gaillard - 13406890 - Série 3 - Projet Final/SOM_C/main.c" -o CMakeFiles/SOM_C.dir/main.c.s

# Object files for target SOM_C
SOM_C_OBJECTS = \
"CMakeFiles/SOM_C.dir/main.c.o"

# External object files for target SOM_C
SOM_C_EXTERNAL_OBJECTS =

SOM_C: CMakeFiles/SOM_C.dir/main.c.o
SOM_C: CMakeFiles/SOM_C.dir/build.make
SOM_C: CMakeFiles/SOM_C.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/solalgaillard/Downloads/Solal Gaillard - 13406890 - Série 3 - Projet Final/SOM_C/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable SOM_C"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SOM_C.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SOM_C.dir/build: SOM_C

.PHONY : CMakeFiles/SOM_C.dir/build

CMakeFiles/SOM_C.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SOM_C.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SOM_C.dir/clean

CMakeFiles/SOM_C.dir/depend:
	cd "/Users/solalgaillard/Downloads/Solal Gaillard - 13406890 - Série 3 - Projet Final/SOM_C/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/solalgaillard/Downloads/Solal Gaillard - 13406890 - Série 3 - Projet Final/SOM_C" "/Users/solalgaillard/Downloads/Solal Gaillard - 13406890 - Série 3 - Projet Final/SOM_C" "/Users/solalgaillard/Downloads/Solal Gaillard - 13406890 - Série 3 - Projet Final/SOM_C/cmake-build-debug" "/Users/solalgaillard/Downloads/Solal Gaillard - 13406890 - Série 3 - Projet Final/SOM_C/cmake-build-debug" "/Users/solalgaillard/Downloads/Solal Gaillard - 13406890 - Série 3 - Projet Final/SOM_C/cmake-build-debug/CMakeFiles/SOM_C.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/SOM_C.dir/depend

