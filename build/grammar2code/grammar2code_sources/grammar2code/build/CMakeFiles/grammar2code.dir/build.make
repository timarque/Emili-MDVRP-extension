# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build

# Include any dependencies generated for this target.
include CMakeFiles/grammar2code.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/grammar2code.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/grammar2code.dir/flags.make

CMakeFiles/grammar2code.dir/src/main.cpp.o: CMakeFiles/grammar2code.dir/flags.make
CMakeFiles/grammar2code.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/grammar2code.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/grammar2code.dir/src/main.cpp.o -c /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/main.cpp

CMakeFiles/grammar2code.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grammar2code.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/main.cpp > CMakeFiles/grammar2code.dir/src/main.cpp.i

CMakeFiles/grammar2code.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grammar2code.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/main.cpp -o CMakeFiles/grammar2code.dir/src/main.cpp.s

# Object files for target grammar2code
grammar2code_OBJECTS = \
"CMakeFiles/grammar2code.dir/src/main.cpp.o"

# External object files for target grammar2code
grammar2code_EXTERNAL_OBJECTS =

grammar2code: CMakeFiles/grammar2code.dir/src/main.cpp.o
grammar2code: CMakeFiles/grammar2code.dir/build.make
grammar2code: libgrammar.a
grammar2code: libpugixml.a
grammar2code: /usr/lib/x86_64-linux-gnu/libboost_program_options.so.1.71.0
grammar2code: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
grammar2code: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
grammar2code: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
grammar2code: CMakeFiles/grammar2code.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable grammar2code"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/grammar2code.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/grammar2code.dir/build: grammar2code

.PHONY : CMakeFiles/grammar2code.dir/build

CMakeFiles/grammar2code.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/grammar2code.dir/cmake_clean.cmake
.PHONY : CMakeFiles/grammar2code.dir/clean

CMakeFiles/grammar2code.dir/depend:
	cd /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build/CMakeFiles/grammar2code.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/grammar2code.dir/depend

