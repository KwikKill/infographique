# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\gabri\Documents\dev\infographique\sampleProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\gabri\Documents\dev\infographique\sampleProject\build

# Include any dependencies generated for this target.
include CMakeFiles/demo_nonrigid.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/demo_nonrigid.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/demo_nonrigid.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/demo_nonrigid.dir/flags.make

CMakeFiles/demo_nonrigid.dir/codegen:
.PHONY : CMakeFiles/demo_nonrigid.dir/codegen

CMakeFiles/demo_nonrigid.dir/demo_nonrigid.cpp.obj: CMakeFiles/demo_nonrigid.dir/flags.make
CMakeFiles/demo_nonrigid.dir/demo_nonrigid.cpp.obj: CMakeFiles/demo_nonrigid.dir/includes_CXX.rsp
CMakeFiles/demo_nonrigid.dir/demo_nonrigid.cpp.obj: C:/Users/gabri/Documents/dev/infographique/sampleProject/demo_nonrigid.cpp
CMakeFiles/demo_nonrigid.dir/demo_nonrigid.cpp.obj: CMakeFiles/demo_nonrigid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\gabri\Documents\dev\infographique\sampleProject\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/demo_nonrigid.dir/demo_nonrigid.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/demo_nonrigid.dir/demo_nonrigid.cpp.obj -MF CMakeFiles\demo_nonrigid.dir\demo_nonrigid.cpp.obj.d -o CMakeFiles\demo_nonrigid.dir\demo_nonrigid.cpp.obj -c C:\Users\gabri\Documents\dev\infographique\sampleProject\demo_nonrigid.cpp

CMakeFiles/demo_nonrigid.dir/demo_nonrigid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/demo_nonrigid.dir/demo_nonrigid.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\gabri\Documents\dev\infographique\sampleProject\demo_nonrigid.cpp > CMakeFiles\demo_nonrigid.dir\demo_nonrigid.cpp.i

CMakeFiles/demo_nonrigid.dir/demo_nonrigid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/demo_nonrigid.dir/demo_nonrigid.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\gabri\Documents\dev\infographique\sampleProject\demo_nonrigid.cpp -o CMakeFiles\demo_nonrigid.dir\demo_nonrigid.cpp.s

# Object files for target demo_nonrigid
demo_nonrigid_OBJECTS = \
"CMakeFiles/demo_nonrigid.dir/demo_nonrigid.cpp.obj"

# External object files for target demo_nonrigid
demo_nonrigid_EXTERNAL_OBJECTS =

demo_nonrigid.exe: CMakeFiles/demo_nonrigid.dir/demo_nonrigid.cpp.obj
demo_nonrigid.exe: CMakeFiles/demo_nonrigid.dir/build.make
demo_nonrigid.exe: C:/Users/gabri/Documents/dev/infographique/sampleProject/../sfmlGraphicsPipeline/build/libSFML_GRAPHICS_PIPELINE.a
demo_nonrigid.exe: C:/Users/gabri/Documents/dev/infographique/sampleProject/../sfmlGraphicsPipeline/extlib/SFML-2.5.1/build/lib/libsfml-system.a
demo_nonrigid.exe: C:/Users/gabri/Documents/dev/infographique/sampleProject/../sfmlGraphicsPipeline/extlib/SFML-2.5.1/build/lib/libsfml-window.a
demo_nonrigid.exe: C:/Users/gabri/Documents/dev/infographique/sampleProject/../sfmlGraphicsPipeline/extlib/SFML-2.5.1/build/lib/libsfml-graphics.a
demo_nonrigid.exe: C:/Users/gabri/Documents/dev/infographique/sampleProject/../sfmlGraphicsPipeline/extlib/glew-1.13.0/lib/glew32.dll
demo_nonrigid.exe: C:/Users/gabri/Documents/dev/infographique/sampleProject/../sfmlGraphicsPipeline/extlib/tinyobjloader/build/libtinyobjloader.a
demo_nonrigid.exe: CMakeFiles/demo_nonrigid.dir/linkLibs.rsp
demo_nonrigid.exe: CMakeFiles/demo_nonrigid.dir/objects1.rsp
demo_nonrigid.exe: CMakeFiles/demo_nonrigid.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\gabri\Documents\dev\infographique\sampleProject\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable demo_nonrigid.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\demo_nonrigid.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/demo_nonrigid.dir/build: demo_nonrigid.exe
.PHONY : CMakeFiles/demo_nonrigid.dir/build

CMakeFiles/demo_nonrigid.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\demo_nonrigid.dir\cmake_clean.cmake
.PHONY : CMakeFiles/demo_nonrigid.dir/clean

CMakeFiles/demo_nonrigid.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\gabri\Documents\dev\infographique\sampleProject C:\Users\gabri\Documents\dev\infographique\sampleProject C:\Users\gabri\Documents\dev\infographique\sampleProject\build C:\Users\gabri\Documents\dev\infographique\sampleProject\build C:\Users\gabri\Documents\dev\infographique\sampleProject\build\CMakeFiles\demo_nonrigid.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/demo_nonrigid.dir/depend
