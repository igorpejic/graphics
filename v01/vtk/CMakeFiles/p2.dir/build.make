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
CMAKE_SOURCE_DIR = /home/igor/graphics/v01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/igor/graphics/v01

# Include any dependencies generated for this target.
include vtk/CMakeFiles/p2.dir/depend.make

# Include the progress variables for this target.
include vtk/CMakeFiles/p2.dir/progress.make

# Include the compile flags for this target's objects.
include vtk/CMakeFiles/p2.dir/flags.make

vtk/CMakeFiles/p2.dir/p2.cpp.o: vtk/CMakeFiles/p2.dir/flags.make
vtk/CMakeFiles/p2.dir/p2.cpp.o: vtk/p2.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/igor/graphics/v01/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object vtk/CMakeFiles/p2.dir/p2.cpp.o"
	cd /home/igor/graphics/v01/vtk && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/p2.dir/p2.cpp.o -c /home/igor/graphics/v01/vtk/p2.cpp

vtk/CMakeFiles/p2.dir/p2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/p2.dir/p2.cpp.i"
	cd /home/igor/graphics/v01/vtk && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/igor/graphics/v01/vtk/p2.cpp > CMakeFiles/p2.dir/p2.cpp.i

vtk/CMakeFiles/p2.dir/p2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/p2.dir/p2.cpp.s"
	cd /home/igor/graphics/v01/vtk && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/igor/graphics/v01/vtk/p2.cpp -o CMakeFiles/p2.dir/p2.cpp.s

vtk/CMakeFiles/p2.dir/p2.cpp.o.requires:
.PHONY : vtk/CMakeFiles/p2.dir/p2.cpp.o.requires

vtk/CMakeFiles/p2.dir/p2.cpp.o.provides: vtk/CMakeFiles/p2.dir/p2.cpp.o.requires
	$(MAKE) -f vtk/CMakeFiles/p2.dir/build.make vtk/CMakeFiles/p2.dir/p2.cpp.o.provides.build
.PHONY : vtk/CMakeFiles/p2.dir/p2.cpp.o.provides

vtk/CMakeFiles/p2.dir/p2.cpp.o.provides.build: vtk/CMakeFiles/p2.dir/p2.cpp.o

# Object files for target p2
p2_OBJECTS = \
"CMakeFiles/p2.dir/p2.cpp.o"

# External object files for target p2
p2_EXTERNAL_OBJECTS =

vtk/p2: vtk/CMakeFiles/p2.dir/p2.cpp.o
vtk/p2: vtk/CMakeFiles/p2.dir/build.make
vtk/p2: /usr/lib/libvtkCommon.so.5.8.0
vtk/p2: /usr/lib/libvtkFiltering.so.5.8.0
vtk/p2: /usr/lib/libvtkImaging.so.5.8.0
vtk/p2: /usr/lib/libvtkGraphics.so.5.8.0
vtk/p2: /usr/lib/libvtkGenericFiltering.so.5.8.0
vtk/p2: /usr/lib/libvtkIO.so.5.8.0
vtk/p2: /usr/lib/libvtkRendering.so.5.8.0
vtk/p2: /usr/lib/libvtkVolumeRendering.so.5.8.0
vtk/p2: /usr/lib/libvtkHybrid.so.5.8.0
vtk/p2: /usr/lib/libvtkWidgets.so.5.8.0
vtk/p2: /usr/lib/libvtkParallel.so.5.8.0
vtk/p2: /usr/lib/libvtkInfovis.so.5.8.0
vtk/p2: /usr/lib/libvtkGeovis.so.5.8.0
vtk/p2: /usr/lib/libvtkViews.so.5.8.0
vtk/p2: /usr/lib/libvtkCharts.so.5.8.0
vtk/p2: /usr/lib/libvtkViews.so.5.8.0
vtk/p2: /usr/lib/libvtkInfovis.so.5.8.0
vtk/p2: /usr/lib/libvtkWidgets.so.5.8.0
vtk/p2: /usr/lib/libvtkVolumeRendering.so.5.8.0
vtk/p2: /usr/lib/libvtkHybrid.so.5.8.0
vtk/p2: /usr/lib/libvtkParallel.so.5.8.0
vtk/p2: /usr/lib/libvtkRendering.so.5.8.0
vtk/p2: /usr/lib/libvtkImaging.so.5.8.0
vtk/p2: /usr/lib/libvtkGraphics.so.5.8.0
vtk/p2: /usr/lib/libvtkIO.so.5.8.0
vtk/p2: /usr/lib/libvtkFiltering.so.5.8.0
vtk/p2: /usr/lib/libvtkCommon.so.5.8.0
vtk/p2: /usr/lib/libvtksys.so.5.8.0
vtk/p2: vtk/CMakeFiles/p2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable p2"
	cd /home/igor/graphics/v01/vtk && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/p2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
vtk/CMakeFiles/p2.dir/build: vtk/p2
.PHONY : vtk/CMakeFiles/p2.dir/build

vtk/CMakeFiles/p2.dir/requires: vtk/CMakeFiles/p2.dir/p2.cpp.o.requires
.PHONY : vtk/CMakeFiles/p2.dir/requires

vtk/CMakeFiles/p2.dir/clean:
	cd /home/igor/graphics/v01/vtk && $(CMAKE_COMMAND) -P CMakeFiles/p2.dir/cmake_clean.cmake
.PHONY : vtk/CMakeFiles/p2.dir/clean

vtk/CMakeFiles/p2.dir/depend:
	cd /home/igor/graphics/v01 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/igor/graphics/v01 /home/igor/graphics/v01/vtk /home/igor/graphics/v01 /home/igor/graphics/v01/vtk /home/igor/graphics/v01/vtk/CMakeFiles/p2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vtk/CMakeFiles/p2.dir/depend

