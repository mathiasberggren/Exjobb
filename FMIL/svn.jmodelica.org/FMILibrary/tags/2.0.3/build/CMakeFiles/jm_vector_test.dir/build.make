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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build

# Include any dependencies generated for this target.
include CMakeFiles/jm_vector_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/jm_vector_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jm_vector_test.dir/flags.make

CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.o: CMakeFiles/jm_vector_test.dir/flags.make
CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.o: ../Test/jm_vector_test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.o   -c /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/Test/jm_vector_test.c

CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/Test/jm_vector_test.c > CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.i

CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/Test/jm_vector_test.c -o CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.s

CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.o.requires:

.PHONY : CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.o.requires

CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.o.provides: CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.o.requires
	$(MAKE) -f CMakeFiles/jm_vector_test.dir/build.make CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.o.provides.build
.PHONY : CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.o.provides

CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.o.provides.build: CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.o


# Object files for target jm_vector_test
jm_vector_test_OBJECTS = \
"CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.o"

# External object files for target jm_vector_test
jm_vector_test_EXTERNAL_OBJECTS =

jm_vector_test: CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.o
jm_vector_test: CMakeFiles/jm_vector_test.dir/build.make
jm_vector_test: libjmutils.a
jm_vector_test: ThirdParty/c99_snprintf/libc99snprintf.a
jm_vector_test: CMakeFiles/jm_vector_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable jm_vector_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jm_vector_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jm_vector_test.dir/build: jm_vector_test

.PHONY : CMakeFiles/jm_vector_test.dir/build

CMakeFiles/jm_vector_test.dir/requires: CMakeFiles/jm_vector_test.dir/Test/jm_vector_test.c.o.requires

.PHONY : CMakeFiles/jm_vector_test.dir/requires

CMakeFiles/jm_vector_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jm_vector_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jm_vector_test.dir/clean

CMakeFiles/jm_vector_test.dir/depend:
	cd /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3 /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3 /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/CMakeFiles/jm_vector_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jm_vector_test.dir/depend
