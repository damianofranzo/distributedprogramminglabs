# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /home/danzio/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/181.4668.70/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/danzio/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/181.4668.70/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/server1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/server1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/server1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server1.dir/flags.make

CMakeFiles/server1.dir/server1_main.c.o: CMakeFiles/server1.dir/flags.make
CMakeFiles/server1.dir/server1_main.c.o: ../server1_main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/server1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/server1.dir/server1_main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server1.dir/server1_main.c.o   -c /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/server1/server1_main.c

CMakeFiles/server1.dir/server1_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server1.dir/server1_main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/server1/server1_main.c > CMakeFiles/server1.dir/server1_main.c.i

CMakeFiles/server1.dir/server1_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server1.dir/server1_main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/server1/server1_main.c -o CMakeFiles/server1.dir/server1_main.c.s

CMakeFiles/server1.dir/server1_main.c.o.requires:

.PHONY : CMakeFiles/server1.dir/server1_main.c.o.requires

CMakeFiles/server1.dir/server1_main.c.o.provides: CMakeFiles/server1.dir/server1_main.c.o.requires
	$(MAKE) -f CMakeFiles/server1.dir/build.make CMakeFiles/server1.dir/server1_main.c.o.provides.build
.PHONY : CMakeFiles/server1.dir/server1_main.c.o.provides

CMakeFiles/server1.dir/server1_main.c.o.provides.build: CMakeFiles/server1.dir/server1_main.c.o


CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.o: CMakeFiles/server1.dir/flags.make
CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.o: /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/server1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.o   -c /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c

CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c > CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.i

CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c -o CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.s

CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.o.requires:

.PHONY : CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.o.requires

CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.o.provides: CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.o.requires
	$(MAKE) -f CMakeFiles/server1.dir/build.make CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.o.provides.build
.PHONY : CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.o.provides

CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.o.provides.build: CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.o


CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.o: CMakeFiles/server1.dir/flags.make
CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.o: /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/server1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.o   -c /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c

CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c > CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.i

CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c -o CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.s

CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.o.requires:

.PHONY : CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.o.requires

CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.o.provides: CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.o.requires
	$(MAKE) -f CMakeFiles/server1.dir/build.make CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.o.provides.build
.PHONY : CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.o.provides

CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.o.provides.build: CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.o


# Object files for target server1
server1_OBJECTS = \
"CMakeFiles/server1.dir/server1_main.c.o" \
"CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.o" \
"CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.o"

# External object files for target server1
server1_EXTERNAL_OBJECTS =

server1: CMakeFiles/server1.dir/server1_main.c.o
server1: CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.o
server1: CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.o
server1: CMakeFiles/server1.dir/build.make
server1: CMakeFiles/server1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/server1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable server1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server1.dir/build: server1

.PHONY : CMakeFiles/server1.dir/build

CMakeFiles/server1.dir/requires: CMakeFiles/server1.dir/server1_main.c.o.requires
CMakeFiles/server1.dir/requires: CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/errlib.c.o.requires
CMakeFiles/server1.dir/requires: CMakeFiles/server1.dir/home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/sockwrap.c.o.requires

.PHONY : CMakeFiles/server1.dir/requires

CMakeFiles/server1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server1.dir/clean

CMakeFiles/server1.dir/depend:
	cd /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/server1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/server1 /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/server1 /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/server1/cmake-build-debug /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/server1/cmake-build-debug /home/danzio/Desktop/programmazione_distribuita/distributedprogramminglabs/lab2_dp1/lab2.3/source/server1/cmake-build-debug/CMakeFiles/server1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server1.dir/depend

