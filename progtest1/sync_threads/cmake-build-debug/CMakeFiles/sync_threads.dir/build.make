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
CMAKE_COMMAND = /home/hawklike/Downloads/clion-2018.1.6/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/hawklike/Downloads/clion-2018.1.6/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hawklike/skola/OSY/progtest1/sync_threads

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hawklike/skola/OSY/progtest1/sync_threads/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/sync_threads.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sync_threads.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sync_threads.dir/flags.make

CMakeFiles/sync_threads.dir/solution.cpp.o: CMakeFiles/sync_threads.dir/flags.make
CMakeFiles/sync_threads.dir/solution.cpp.o: ../solution.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hawklike/skola/OSY/progtest1/sync_threads/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sync_threads.dir/solution.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sync_threads.dir/solution.cpp.o -c /home/hawklike/skola/OSY/progtest1/sync_threads/solution.cpp

CMakeFiles/sync_threads.dir/solution.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sync_threads.dir/solution.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hawklike/skola/OSY/progtest1/sync_threads/solution.cpp > CMakeFiles/sync_threads.dir/solution.cpp.i

CMakeFiles/sync_threads.dir/solution.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sync_threads.dir/solution.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hawklike/skola/OSY/progtest1/sync_threads/solution.cpp -o CMakeFiles/sync_threads.dir/solution.cpp.s

CMakeFiles/sync_threads.dir/solution.cpp.o.requires:

.PHONY : CMakeFiles/sync_threads.dir/solution.cpp.o.requires

CMakeFiles/sync_threads.dir/solution.cpp.o.provides: CMakeFiles/sync_threads.dir/solution.cpp.o.requires
	$(MAKE) -f CMakeFiles/sync_threads.dir/build.make CMakeFiles/sync_threads.dir/solution.cpp.o.provides.build
.PHONY : CMakeFiles/sync_threads.dir/solution.cpp.o.provides

CMakeFiles/sync_threads.dir/solution.cpp.o.provides.build: CMakeFiles/sync_threads.dir/solution.cpp.o


CMakeFiles/sync_threads.dir/sample_tester.cpp.o: CMakeFiles/sync_threads.dir/flags.make
CMakeFiles/sync_threads.dir/sample_tester.cpp.o: ../sample_tester.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hawklike/skola/OSY/progtest1/sync_threads/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sync_threads.dir/sample_tester.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sync_threads.dir/sample_tester.cpp.o -c /home/hawklike/skola/OSY/progtest1/sync_threads/sample_tester.cpp

CMakeFiles/sync_threads.dir/sample_tester.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sync_threads.dir/sample_tester.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hawklike/skola/OSY/progtest1/sync_threads/sample_tester.cpp > CMakeFiles/sync_threads.dir/sample_tester.cpp.i

CMakeFiles/sync_threads.dir/sample_tester.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sync_threads.dir/sample_tester.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hawklike/skola/OSY/progtest1/sync_threads/sample_tester.cpp -o CMakeFiles/sync_threads.dir/sample_tester.cpp.s

CMakeFiles/sync_threads.dir/sample_tester.cpp.o.requires:

.PHONY : CMakeFiles/sync_threads.dir/sample_tester.cpp.o.requires

CMakeFiles/sync_threads.dir/sample_tester.cpp.o.provides: CMakeFiles/sync_threads.dir/sample_tester.cpp.o.requires
	$(MAKE) -f CMakeFiles/sync_threads.dir/build.make CMakeFiles/sync_threads.dir/sample_tester.cpp.o.provides.build
.PHONY : CMakeFiles/sync_threads.dir/sample_tester.cpp.o.provides

CMakeFiles/sync_threads.dir/sample_tester.cpp.o.provides.build: CMakeFiles/sync_threads.dir/sample_tester.cpp.o


# Object files for target sync_threads
sync_threads_OBJECTS = \
"CMakeFiles/sync_threads.dir/solution.cpp.o" \
"CMakeFiles/sync_threads.dir/sample_tester.cpp.o"

# External object files for target sync_threads
sync_threads_EXTERNAL_OBJECTS =

sync_threads: CMakeFiles/sync_threads.dir/solution.cpp.o
sync_threads: CMakeFiles/sync_threads.dir/sample_tester.cpp.o
sync_threads: CMakeFiles/sync_threads.dir/build.make
sync_threads: CMakeFiles/sync_threads.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hawklike/skola/OSY/progtest1/sync_threads/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable sync_threads"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sync_threads.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sync_threads.dir/build: sync_threads

.PHONY : CMakeFiles/sync_threads.dir/build

CMakeFiles/sync_threads.dir/requires: CMakeFiles/sync_threads.dir/solution.cpp.o.requires
CMakeFiles/sync_threads.dir/requires: CMakeFiles/sync_threads.dir/sample_tester.cpp.o.requires

.PHONY : CMakeFiles/sync_threads.dir/requires

CMakeFiles/sync_threads.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sync_threads.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sync_threads.dir/clean

CMakeFiles/sync_threads.dir/depend:
	cd /home/hawklike/skola/OSY/progtest1/sync_threads/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hawklike/skola/OSY/progtest1/sync_threads /home/hawklike/skola/OSY/progtest1/sync_threads /home/hawklike/skola/OSY/progtest1/sync_threads/cmake-build-debug /home/hawklike/skola/OSY/progtest1/sync_threads/cmake-build-debug /home/hawklike/skola/OSY/progtest1/sync_threads/cmake-build-debug/CMakeFiles/sync_threads.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sync_threads.dir/depend

