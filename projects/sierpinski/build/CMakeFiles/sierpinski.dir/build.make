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
CMAKE_SOURCE_DIR = /home/gacel/TFGacel/projects/sierpinski/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gacel/TFGacel/projects/sierpinski/build

# Include any dependencies generated for this target.
include CMakeFiles/sierpinski.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sierpinski.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sierpinski.dir/flags.make

CMakeFiles/sierpinski.dir/main.cpp.o: CMakeFiles/sierpinski.dir/flags.make
CMakeFiles/sierpinski.dir/main.cpp.o: /home/gacel/TFGacel/projects/sierpinski/src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gacel/TFGacel/projects/sierpinski/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sierpinski.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sierpinski.dir/main.cpp.o -c /home/gacel/TFGacel/projects/sierpinski/src/main.cpp

CMakeFiles/sierpinski.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sierpinski.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gacel/TFGacel/projects/sierpinski/src/main.cpp > CMakeFiles/sierpinski.dir/main.cpp.i

CMakeFiles/sierpinski.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sierpinski.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gacel/TFGacel/projects/sierpinski/src/main.cpp -o CMakeFiles/sierpinski.dir/main.cpp.s

CMakeFiles/sierpinski.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/sierpinski.dir/main.cpp.o.requires

CMakeFiles/sierpinski.dir/main.cpp.o.provides: CMakeFiles/sierpinski.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/sierpinski.dir/build.make CMakeFiles/sierpinski.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/sierpinski.dir/main.cpp.o.provides

CMakeFiles/sierpinski.dir/main.cpp.o.provides.build: CMakeFiles/sierpinski.dir/main.cpp.o

# Object files for target sierpinski
sierpinski_OBJECTS = \
"CMakeFiles/sierpinski.dir/main.cpp.o"

# External object files for target sierpinski
sierpinski_EXTERNAL_OBJECTS =

sierpinski: CMakeFiles/sierpinski.dir/main.cpp.o
sierpinski: CMakeFiles/sierpinski.dir/build.make
sierpinski: /usr/lib/x86_64-linux-gnu/libboost_system.so
sierpinski: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
sierpinski: /usr/lib/x86_64-linux-gnu/libboost_thread.so
sierpinski: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
sierpinski: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so
sierpinski: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
sierpinski: /usr/lib/x86_64-linux-gnu/libpthread.so
sierpinski: /usr/lib/libpcl_common.so
sierpinski: /usr/lib/libpcl_octree.so
sierpinski: /usr/lib/libOpenNI.so
sierpinski: /usr/lib/libvtkCommon.so.5.8.0
sierpinski: /usr/lib/libvtkRendering.so.5.8.0
sierpinski: /usr/lib/libvtkHybrid.so.5.8.0
sierpinski: /usr/lib/libvtkCharts.so.5.8.0
sierpinski: /usr/lib/libpcl_io.so
sierpinski: /usr/lib/x86_64-linux-gnu/libflann_cpp_s.a
sierpinski: /usr/lib/libpcl_kdtree.so
sierpinski: /usr/lib/libpcl_search.so
sierpinski: /usr/lib/libpcl_sample_consensus.so
sierpinski: /usr/lib/libpcl_filters.so
sierpinski: /usr/lib/libpcl_features.so
sierpinski: /usr/lib/libpcl_keypoints.so
sierpinski: /usr/lib/libpcl_segmentation.so
sierpinski: /usr/lib/libpcl_visualization.so
sierpinski: /usr/lib/libpcl_outofcore.so
sierpinski: /usr/lib/libpcl_registration.so
sierpinski: /usr/lib/libpcl_recognition.so
sierpinski: /usr/lib/x86_64-linux-gnu/libqhull.so
sierpinski: /usr/lib/libpcl_surface.so
sierpinski: /usr/lib/libpcl_people.so
sierpinski: /usr/lib/libpcl_tracking.so
sierpinski: /usr/lib/libpcl_apps.so
sierpinski: /usr/lib/x86_64-linux-gnu/libboost_system.so
sierpinski: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
sierpinski: /usr/lib/x86_64-linux-gnu/libboost_thread.so
sierpinski: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
sierpinski: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so
sierpinski: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
sierpinski: /usr/lib/x86_64-linux-gnu/libpthread.so
sierpinski: /usr/lib/x86_64-linux-gnu/libqhull.so
sierpinski: /usr/lib/libOpenNI.so
sierpinski: /usr/lib/x86_64-linux-gnu/libflann_cpp_s.a
sierpinski: /usr/lib/libvtkCommon.so.5.8.0
sierpinski: /usr/lib/libvtkRendering.so.5.8.0
sierpinski: /usr/lib/libvtkHybrid.so.5.8.0
sierpinski: /usr/lib/libvtkCharts.so.5.8.0
sierpinski: /usr/lib/libpcl_common.so
sierpinski: /usr/lib/libpcl_octree.so
sierpinski: /usr/lib/libpcl_io.so
sierpinski: /usr/lib/libpcl_kdtree.so
sierpinski: /usr/lib/libpcl_search.so
sierpinski: /usr/lib/libpcl_sample_consensus.so
sierpinski: /usr/lib/libpcl_filters.so
sierpinski: /usr/lib/libpcl_features.so
sierpinski: /usr/lib/libpcl_keypoints.so
sierpinski: /usr/lib/libpcl_segmentation.so
sierpinski: /usr/lib/libpcl_visualization.so
sierpinski: /usr/lib/libpcl_outofcore.so
sierpinski: /usr/lib/libpcl_registration.so
sierpinski: /usr/lib/libpcl_recognition.so
sierpinski: /usr/lib/libpcl_surface.so
sierpinski: /usr/lib/libpcl_people.so
sierpinski: /usr/lib/libpcl_tracking.so
sierpinski: /usr/lib/libpcl_apps.so
sierpinski: /usr/lib/libvtkViews.so.5.8.0
sierpinski: /usr/lib/libvtkInfovis.so.5.8.0
sierpinski: /usr/lib/libvtkWidgets.so.5.8.0
sierpinski: /usr/lib/libvtkHybrid.so.5.8.0
sierpinski: /usr/lib/libvtkParallel.so.5.8.0
sierpinski: /usr/lib/libvtkVolumeRendering.so.5.8.0
sierpinski: /usr/lib/libvtkRendering.so.5.8.0
sierpinski: /usr/lib/libvtkGraphics.so.5.8.0
sierpinski: /usr/lib/libvtkImaging.so.5.8.0
sierpinski: /usr/lib/libvtkIO.so.5.8.0
sierpinski: /usr/lib/libvtkFiltering.so.5.8.0
sierpinski: /usr/lib/libvtkCommon.so.5.8.0
sierpinski: /usr/lib/libvtksys.so.5.8.0
sierpinski: CMakeFiles/sierpinski.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable sierpinski"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sierpinski.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sierpinski.dir/build: sierpinski
.PHONY : CMakeFiles/sierpinski.dir/build

CMakeFiles/sierpinski.dir/requires: CMakeFiles/sierpinski.dir/main.cpp.o.requires
.PHONY : CMakeFiles/sierpinski.dir/requires

CMakeFiles/sierpinski.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sierpinski.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sierpinski.dir/clean

CMakeFiles/sierpinski.dir/depend:
	cd /home/gacel/TFGacel/projects/sierpinski/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gacel/TFGacel/projects/sierpinski/src /home/gacel/TFGacel/projects/sierpinski/src /home/gacel/TFGacel/projects/sierpinski/build /home/gacel/TFGacel/projects/sierpinski/build /home/gacel/TFGacel/projects/sierpinski/build/CMakeFiles/sierpinski.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sierpinski.dir/depend

