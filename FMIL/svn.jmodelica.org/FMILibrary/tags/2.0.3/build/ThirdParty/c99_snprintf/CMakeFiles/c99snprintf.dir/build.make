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
include ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/depend.make

# Include the progress variables for this target.
include ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/progress.make

# Include the compile flags for this target's objects.
include ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/flags.make

ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.o: ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/flags.make
ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.o: ../ThirdParty/c99_snprintf/c99-snprintf_1.1/snprintf.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.o"
	cd /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/ThirdParty/c99_snprintf && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.o   -c /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/ThirdParty/c99_snprintf/c99-snprintf_1.1/snprintf.c

ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.i"
	cd /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/ThirdParty/c99_snprintf && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/ThirdParty/c99_snprintf/c99-snprintf_1.1/snprintf.c > CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.i

ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.s"
	cd /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/ThirdParty/c99_snprintf && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/ThirdParty/c99_snprintf/c99-snprintf_1.1/snprintf.c -o CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.s

ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.o.requires:

.PHONY : ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.o.requires

ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.o.provides: ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.o.requires
	$(MAKE) -f ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/build.make ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.o.provides.build
.PHONY : ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.o.provides

ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.o.provides.build: ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.o


# Object files for target c99snprintf
c99snprintf_OBJECTS = \
"CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.o"

# External object files for target c99snprintf
c99snprintf_EXTERNAL_OBJECTS =

ThirdParty/c99_snprintf/libc99snprintf.a: ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.o
ThirdParty/c99_snprintf/libc99snprintf.a: ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/build.make
ThirdParty/c99_snprintf/libc99snprintf.a: ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libc99snprintf.a"
	cd /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/ThirdParty/c99_snprintf && $(CMAKE_COMMAND) -P CMakeFiles/c99snprintf.dir/cmake_clean_target.cmake
	cd /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/ThirdParty/c99_snprintf && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/c99snprintf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/build: ThirdParty/c99_snprintf/libc99snprintf.a

.PHONY : ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/build

ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/requires: ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/c99-snprintf_1.1/snprintf.c.o.requires

.PHONY : ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/requires

ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/clean:
	cd /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/ThirdParty/c99_snprintf && $(CMAKE_COMMAND) -P CMakeFiles/c99snprintf.dir/cmake_clean.cmake
.PHONY : ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/clean

ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/depend:
	cd /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3 /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/ThirdParty/c99_snprintf /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/ThirdParty/c99_snprintf /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ThirdParty/c99_snprintf/CMakeFiles/c99snprintf.dir/depend

