# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\ivano\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\173.4674.29\bin\cmake\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\ivano\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\173.4674.29\bin\cmake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\ivano\Documents\Snake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\ivano\Documents\Snake\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Snake.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Snake.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Snake.dir/flags.make

CMakeFiles/Snake.dir/main.c.obj: CMakeFiles/Snake.dir/flags.make
CMakeFiles/Snake.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ivano\Documents\Snake\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Snake.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Snake.dir\main.c.obj   -c C:\Users\ivano\Documents\Snake\main.c

CMakeFiles/Snake.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Snake.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\ivano\Documents\Snake\main.c > CMakeFiles\Snake.dir\main.c.i

CMakeFiles/Snake.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Snake.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\ivano\Documents\Snake\main.c -o CMakeFiles\Snake.dir\main.c.s

CMakeFiles/Snake.dir/main.c.obj.requires:

.PHONY : CMakeFiles/Snake.dir/main.c.obj.requires

CMakeFiles/Snake.dir/main.c.obj.provides: CMakeFiles/Snake.dir/main.c.obj.requires
	$(MAKE) -f CMakeFiles\Snake.dir\build.make CMakeFiles/Snake.dir/main.c.obj.provides.build
.PHONY : CMakeFiles/Snake.dir/main.c.obj.provides

CMakeFiles/Snake.dir/main.c.obj.provides.build: CMakeFiles/Snake.dir/main.c.obj


# Object files for target Snake
Snake_OBJECTS = \
"CMakeFiles/Snake.dir/main.c.obj"

# External object files for target Snake
Snake_EXTERNAL_OBJECTS =

Snake.exe: CMakeFiles/Snake.dir/main.c.obj
Snake.exe: CMakeFiles/Snake.dir/build.make
Snake.exe: CMakeFiles/Snake.dir/linklibs.rsp
Snake.exe: CMakeFiles/Snake.dir/objects1.rsp
Snake.exe: CMakeFiles/Snake.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\ivano\Documents\Snake\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Snake.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Snake.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Snake.dir/build: Snake.exe

.PHONY : CMakeFiles/Snake.dir/build

CMakeFiles/Snake.dir/requires: CMakeFiles/Snake.dir/main.c.obj.requires

.PHONY : CMakeFiles/Snake.dir/requires

CMakeFiles/Snake.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Snake.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Snake.dir/clean

CMakeFiles/Snake.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\ivano\Documents\Snake C:\Users\ivano\Documents\Snake C:\Users\ivano\Documents\Snake\cmake-build-debug C:\Users\ivano\Documents\Snake\cmake-build-debug C:\Users\ivano\Documents\Snake\cmake-build-debug\CMakeFiles\Snake.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Snake.dir/depend
