# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/igor/graphics/SimpleCone

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/igor/graphics/SimpleCone

# Include any dependencies generated for this target.
include Step2/CMakeFiles/Step2.dir/depend.make

# Include the progress variables for this target.
include Step2/CMakeFiles/Step2.dir/progress.make

# Include the compile flags for this target's objects.
include Step2/CMakeFiles/Step2.dir/flags.make

Step2/CMakeFiles/Step2.dir/Cone.cpp.o: Step2/CMakeFiles/Step2.dir/flags.make
Step2/CMakeFiles/Step2.dir/Cone.cpp.o: Step2/Cone.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/igor/graphics/SimpleCone/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Step2/CMakeFiles/Step2.dir/Cone.cpp.o"
	cd /home/igor/graphics/SimpleCone/Step2 && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Step2.dir/Cone.cpp.o -c /home/igor/graphics/SimpleCone/Step2/Cone.cpp

Step2/CMakeFiles/Step2.dir/Cone.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Step2.dir/Cone.cpp.i"
	cd /home/igor/graphics/SimpleCone/Step2 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/igor/graphics/SimpleCone/Step2/Cone.cpp > CMakeFiles/Step2.dir/Cone.cpp.i

Step2/CMakeFiles/Step2.dir/Cone.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Step2.dir/Cone.cpp.s"
	cd /home/igor/graphics/SimpleCone/Step2 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/igor/graphics/SimpleCone/Step2/Cone.cpp -o CMakeFiles/Step2.dir/Cone.cpp.s

Step2/CMakeFiles/Step2.dir/Cone.cpp.o.requires:
.PHONY : Step2/CMakeFiles/Step2.dir/Cone.cpp.o.requires

Step2/CMakeFiles/Step2.dir/Cone.cpp.o.provides: Step2/CMakeFiles/Step2.dir/Cone.cpp.o.requires
	$(MAKE) -f Step2/CMakeFiles/Step2.dir/build.make Step2/CMakeFiles/Step2.dir/Cone.cpp.o.provides.build
.PHONY : Step2/CMakeFiles/Step2.dir/Cone.cpp.o.provides

Step2/CMakeFiles/Step2.dir/Cone.cpp.o.provides.build: Step2/CMakeFiles/Step2.dir/Cone.cpp.o

# Object files for target Step2
Step2_OBJECTS = \
"CMakeFiles/Step2.dir/Cone.cpp.o"

# External object files for target Step2
Step2_EXTERNAL_OBJECTS =

Step2/Step2: Step2/CMakeFiles/Step2.dir/Cone.cpp.o
Step2/Step2: Step2/CMakeFiles/Step2.dir/build.make
Step2/Step2: /usr/lib/libvtkRendering.so.5.8.0
Step2/Step2: /usr/lib/libvtkGraphics.so.5.8.0
Step2/Step2: /usr/lib/libvtkImaging.so.5.8.0
Step2/Step2: /usr/lib/libvtkFiltering.so.5.8.0
Step2/Step2: /usr/lib/libvtkCommon.so.5.8.0
Step2/Step2: /usr/lib/libvtksys.so.5.8.0
Step2/Step2: Step2/CMakeFiles/Step2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Step2"
	cd /home/igor/graphics/SimpleCone/Step2 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Step2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Step2/CMakeFiles/Step2.dir/build: Step2/Step2
.PHONY : Step2/CMakeFiles/Step2.dir/build

Step2/CMakeFiles/Step2.dir/requires: Step2/CMakeFiles/Step2.dir/Cone.cpp.o.requires
.PHONY : Step2/CMakeFiles/Step2.dir/requires

Step2/CMakeFiles/Step2.dir/clean:
	cd /home/igor/graphics/SimpleCone/Step2 && $(CMAKE_COMMAND) -P CMakeFiles/Step2.dir/cmake_clean.cmake
.PHONY : Step2/CMakeFiles/Step2.dir/clean

Step2/CMakeFiles/Step2.dir/depend:
	cd /home/igor/graphics/SimpleCone && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/igor/graphics/SimpleCone /home/igor/graphics/SimpleCone/Step2 /home/igor/graphics/SimpleCone /home/igor/graphics/SimpleCone/Step2 /home/igor/graphics/SimpleCone/Step2/CMakeFiles/Step2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Step2/CMakeFiles/Step2.dir/depend

