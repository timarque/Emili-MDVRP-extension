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
include CMakeFiles/grammar.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/grammar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/grammar.dir/flags.make

CMakeFiles/grammar.dir/src/model.cpp.o: CMakeFiles/grammar.dir/flags.make
CMakeFiles/grammar.dir/src/model.cpp.o: ../src/model.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/grammar.dir/src/model.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/grammar.dir/src/model.cpp.o -c /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/model.cpp

CMakeFiles/grammar.dir/src/model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grammar.dir/src/model.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/model.cpp > CMakeFiles/grammar.dir/src/model.cpp.i

CMakeFiles/grammar.dir/src/model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grammar.dir/src/model.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/model.cpp -o CMakeFiles/grammar.dir/src/model.cpp.s

CMakeFiles/grammar.dir/src/walker.cpp.o: CMakeFiles/grammar.dir/flags.make
CMakeFiles/grammar.dir/src/walker.cpp.o: ../src/walker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/grammar.dir/src/walker.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/grammar.dir/src/walker.cpp.o -c /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/walker.cpp

CMakeFiles/grammar.dir/src/walker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grammar.dir/src/walker.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/walker.cpp > CMakeFiles/grammar.dir/src/walker.cpp.i

CMakeFiles/grammar.dir/src/walker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grammar.dir/src/walker.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/walker.cpp -o CMakeFiles/grammar.dir/src/walker.cpp.s

CMakeFiles/grammar.dir/src/configuration.cpp.o: CMakeFiles/grammar.dir/flags.make
CMakeFiles/grammar.dir/src/configuration.cpp.o: ../src/configuration.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/grammar.dir/src/configuration.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/grammar.dir/src/configuration.cpp.o -c /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/configuration.cpp

CMakeFiles/grammar.dir/src/configuration.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grammar.dir/src/configuration.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/configuration.cpp > CMakeFiles/grammar.dir/src/configuration.cpp.i

CMakeFiles/grammar.dir/src/configuration.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grammar.dir/src/configuration.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/configuration.cpp -o CMakeFiles/grammar.dir/src/configuration.cpp.s

CMakeFiles/grammar.dir/src/irace_conf.cpp.o: CMakeFiles/grammar.dir/flags.make
CMakeFiles/grammar.dir/src/irace_conf.cpp.o: ../src/irace_conf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/grammar.dir/src/irace_conf.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/grammar.dir/src/irace_conf.cpp.o -c /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/irace_conf.cpp

CMakeFiles/grammar.dir/src/irace_conf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grammar.dir/src/irace_conf.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/irace_conf.cpp > CMakeFiles/grammar.dir/src/irace_conf.cpp.i

CMakeFiles/grammar.dir/src/irace_conf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grammar.dir/src/irace_conf.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/irace_conf.cpp -o CMakeFiles/grammar.dir/src/irace_conf.cpp.s

CMakeFiles/grammar.dir/src/paramils_conf.cpp.o: CMakeFiles/grammar.dir/flags.make
CMakeFiles/grammar.dir/src/paramils_conf.cpp.o: ../src/paramils_conf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/grammar.dir/src/paramils_conf.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/grammar.dir/src/paramils_conf.cpp.o -c /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/paramils_conf.cpp

CMakeFiles/grammar.dir/src/paramils_conf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grammar.dir/src/paramils_conf.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/paramils_conf.cpp > CMakeFiles/grammar.dir/src/paramils_conf.cpp.i

CMakeFiles/grammar.dir/src/paramils_conf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grammar.dir/src/paramils_conf.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/paramils_conf.cpp -o CMakeFiles/grammar.dir/src/paramils_conf.cpp.s

CMakeFiles/grammar.dir/src/smac_conf.cpp.o: CMakeFiles/grammar.dir/flags.make
CMakeFiles/grammar.dir/src/smac_conf.cpp.o: ../src/smac_conf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/grammar.dir/src/smac_conf.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/grammar.dir/src/smac_conf.cpp.o -c /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/smac_conf.cpp

CMakeFiles/grammar.dir/src/smac_conf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grammar.dir/src/smac_conf.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/smac_conf.cpp > CMakeFiles/grammar.dir/src/smac_conf.cpp.i

CMakeFiles/grammar.dir/src/smac_conf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grammar.dir/src/smac_conf.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/smac_conf.cpp -o CMakeFiles/grammar.dir/src/smac_conf.cpp.s

CMakeFiles/grammar.dir/src/error.cpp.o: CMakeFiles/grammar.dir/flags.make
CMakeFiles/grammar.dir/src/error.cpp.o: ../src/error.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/grammar.dir/src/error.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/grammar.dir/src/error.cpp.o -c /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/error.cpp

CMakeFiles/grammar.dir/src/error.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grammar.dir/src/error.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/error.cpp > CMakeFiles/grammar.dir/src/error.cpp.i

CMakeFiles/grammar.dir/src/error.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grammar.dir/src/error.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/error.cpp -o CMakeFiles/grammar.dir/src/error.cpp.s

CMakeFiles/grammar.dir/src/params2code.cpp.o: CMakeFiles/grammar.dir/flags.make
CMakeFiles/grammar.dir/src/params2code.cpp.o: ../src/params2code.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/grammar.dir/src/params2code.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/grammar.dir/src/params2code.cpp.o -c /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/params2code.cpp

CMakeFiles/grammar.dir/src/params2code.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grammar.dir/src/params2code.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/params2code.cpp > CMakeFiles/grammar.dir/src/params2code.cpp.i

CMakeFiles/grammar.dir/src/params2code.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grammar.dir/src/params2code.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/src/params2code.cpp -o CMakeFiles/grammar.dir/src/params2code.cpp.s

# Object files for target grammar
grammar_OBJECTS = \
"CMakeFiles/grammar.dir/src/model.cpp.o" \
"CMakeFiles/grammar.dir/src/walker.cpp.o" \
"CMakeFiles/grammar.dir/src/configuration.cpp.o" \
"CMakeFiles/grammar.dir/src/irace_conf.cpp.o" \
"CMakeFiles/grammar.dir/src/paramils_conf.cpp.o" \
"CMakeFiles/grammar.dir/src/smac_conf.cpp.o" \
"CMakeFiles/grammar.dir/src/error.cpp.o" \
"CMakeFiles/grammar.dir/src/params2code.cpp.o"

# External object files for target grammar
grammar_EXTERNAL_OBJECTS =

libgrammar.a: CMakeFiles/grammar.dir/src/model.cpp.o
libgrammar.a: CMakeFiles/grammar.dir/src/walker.cpp.o
libgrammar.a: CMakeFiles/grammar.dir/src/configuration.cpp.o
libgrammar.a: CMakeFiles/grammar.dir/src/irace_conf.cpp.o
libgrammar.a: CMakeFiles/grammar.dir/src/paramils_conf.cpp.o
libgrammar.a: CMakeFiles/grammar.dir/src/smac_conf.cpp.o
libgrammar.a: CMakeFiles/grammar.dir/src/error.cpp.o
libgrammar.a: CMakeFiles/grammar.dir/src/params2code.cpp.o
libgrammar.a: CMakeFiles/grammar.dir/build.make
libgrammar.a: CMakeFiles/grammar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX static library libgrammar.a"
	$(CMAKE_COMMAND) -P CMakeFiles/grammar.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/grammar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/grammar.dir/build: libgrammar.a

.PHONY : CMakeFiles/grammar.dir/build

CMakeFiles/grammar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/grammar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/grammar.dir/clean

CMakeFiles/grammar.dir/depend:
	cd /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build /home/tagotuga/Emili-MDVRP-extension/build/grammar2code/grammar2code_sources/grammar2code/build/CMakeFiles/grammar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/grammar.dir/depend

