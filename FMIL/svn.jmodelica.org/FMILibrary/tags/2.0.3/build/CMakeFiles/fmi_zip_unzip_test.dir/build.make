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
include CMakeFiles/fmi_zip_unzip_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fmi_zip_unzip_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fmi_zip_unzip_test.dir/flags.make

CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.o: CMakeFiles/fmi_zip_unzip_test.dir/flags.make
CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.o: ../Test/FMI1/fmi_zip_unzip_test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.o   -c /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/Test/FMI1/fmi_zip_unzip_test.c

CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/Test/FMI1/fmi_zip_unzip_test.c > CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.i

CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/Test/FMI1/fmi_zip_unzip_test.c -o CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.s

CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.o.requires:

.PHONY : CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.o.requires

CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.o.provides: CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.o.requires
	$(MAKE) -f CMakeFiles/fmi_zip_unzip_test.dir/build.make CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.o.provides.build
.PHONY : CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.o.provides

CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.o.provides.build: CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.o


# Object files for target fmi_zip_unzip_test
fmi_zip_unzip_test_OBJECTS = \
"CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.o"

# External object files for target fmi_zip_unzip_test
fmi_zip_unzip_test_EXTERNAL_OBJECTS =

fmi_zip_unzip_test: CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.o
fmi_zip_unzip_test: CMakeFiles/fmi_zip_unzip_test.dir/build.make
fmi_zip_unzip_test: libfmizip.a
fmi_zip_unzip_test: Config.cmake/Minizip/libminizip.a
fmi_zip_unzip_test: zlib/libz.a
fmi_zip_unzip_test: libjmutils.a
fmi_zip_unzip_test: ThirdParty/c99_snprintf/libc99snprintf.a
fmi_zip_unzip_test: CMakeFiles/fmi_zip_unzip_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable fmi_zip_unzip_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fmi_zip_unzip_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fmi_zip_unzip_test.dir/build: fmi_zip_unzip_test

.PHONY : CMakeFiles/fmi_zip_unzip_test.dir/build

CMakeFiles/fmi_zip_unzip_test.dir/requires: CMakeFiles/fmi_zip_unzip_test.dir/Test/FMI1/fmi_zip_unzip_test.c.o.requires

.PHONY : CMakeFiles/fmi_zip_unzip_test.dir/requires

CMakeFiles/fmi_zip_unzip_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fmi_zip_unzip_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fmi_zip_unzip_test.dir/clean

CMakeFiles/fmi_zip_unzip_test.dir/depend:
	cd /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3 /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3 /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/CMakeFiles/fmi_zip_unzip_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fmi_zip_unzip_test.dir/depend

