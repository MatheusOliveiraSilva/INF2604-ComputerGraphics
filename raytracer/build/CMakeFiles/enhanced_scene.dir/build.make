# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/matheussilva/Documents/masters/INF2604-ComputerGraphics/raytracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/matheussilva/Documents/masters/INF2604-ComputerGraphics/raytracer/build

# Include any dependencies generated for this target.
include CMakeFiles/enhanced_scene.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/enhanced_scene.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/enhanced_scene.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/enhanced_scene.dir/flags.make

CMakeFiles/enhanced_scene.dir/codegen:
.PHONY : CMakeFiles/enhanced_scene.dir/codegen

CMakeFiles/enhanced_scene.dir/examples/enhanced_scene.cpp.o: CMakeFiles/enhanced_scene.dir/flags.make
CMakeFiles/enhanced_scene.dir/examples/enhanced_scene.cpp.o: /Users/matheussilva/Documents/masters/INF2604-ComputerGraphics/raytracer/examples/enhanced_scene.cpp
CMakeFiles/enhanced_scene.dir/examples/enhanced_scene.cpp.o: CMakeFiles/enhanced_scene.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/matheussilva/Documents/masters/INF2604-ComputerGraphics/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/enhanced_scene.dir/examples/enhanced_scene.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/enhanced_scene.dir/examples/enhanced_scene.cpp.o -MF CMakeFiles/enhanced_scene.dir/examples/enhanced_scene.cpp.o.d -o CMakeFiles/enhanced_scene.dir/examples/enhanced_scene.cpp.o -c /Users/matheussilva/Documents/masters/INF2604-ComputerGraphics/raytracer/examples/enhanced_scene.cpp

CMakeFiles/enhanced_scene.dir/examples/enhanced_scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/enhanced_scene.dir/examples/enhanced_scene.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/matheussilva/Documents/masters/INF2604-ComputerGraphics/raytracer/examples/enhanced_scene.cpp > CMakeFiles/enhanced_scene.dir/examples/enhanced_scene.cpp.i

CMakeFiles/enhanced_scene.dir/examples/enhanced_scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/enhanced_scene.dir/examples/enhanced_scene.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/matheussilva/Documents/masters/INF2604-ComputerGraphics/raytracer/examples/enhanced_scene.cpp -o CMakeFiles/enhanced_scene.dir/examples/enhanced_scene.cpp.s

# Object files for target enhanced_scene
enhanced_scene_OBJECTS = \
"CMakeFiles/enhanced_scene.dir/examples/enhanced_scene.cpp.o"

# External object files for target enhanced_scene
enhanced_scene_EXTERNAL_OBJECTS =

bin/enhanced_scene: CMakeFiles/enhanced_scene.dir/examples/enhanced_scene.cpp.o
bin/enhanced_scene: CMakeFiles/enhanced_scene.dir/build.make
bin/enhanced_scene: CMakeFiles/enhanced_scene.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/matheussilva/Documents/masters/INF2604-ComputerGraphics/raytracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/enhanced_scene"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/enhanced_scene.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/enhanced_scene.dir/build: bin/enhanced_scene
.PHONY : CMakeFiles/enhanced_scene.dir/build

CMakeFiles/enhanced_scene.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/enhanced_scene.dir/cmake_clean.cmake
.PHONY : CMakeFiles/enhanced_scene.dir/clean

CMakeFiles/enhanced_scene.dir/depend:
	cd /Users/matheussilva/Documents/masters/INF2604-ComputerGraphics/raytracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/matheussilva/Documents/masters/INF2604-ComputerGraphics/raytracer /Users/matheussilva/Documents/masters/INF2604-ComputerGraphics/raytracer /Users/matheussilva/Documents/masters/INF2604-ComputerGraphics/raytracer/build /Users/matheussilva/Documents/masters/INF2604-ComputerGraphics/raytracer/build /Users/matheussilva/Documents/masters/INF2604-ComputerGraphics/raytracer/build/CMakeFiles/enhanced_scene.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/enhanced_scene.dir/depend

