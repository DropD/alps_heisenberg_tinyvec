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
CMAKE_COMMAND = /usr/local/Cellar/cmake/2.8.12.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/2.8.12.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/local/Cellar/cmake/2.8.12.1/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/build

# Include any dependencies generated for this target.
include CMakeFiles/single.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/single.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/single.dir/flags.make

CMakeFiles/single.dir/ising.cpp.o: CMakeFiles/single.dir/flags.make
CMakeFiles/single.dir/ising.cpp.o: ../ising.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/single.dir/ising.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/single.dir/ising.cpp.o -c /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/ising.cpp

CMakeFiles/single.dir/ising.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/single.dir/ising.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/ising.cpp > CMakeFiles/single.dir/ising.cpp.i

CMakeFiles/single.dir/ising.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/single.dir/ising.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/ising.cpp -o CMakeFiles/single.dir/ising.cpp.s

CMakeFiles/single.dir/ising.cpp.o.requires:
.PHONY : CMakeFiles/single.dir/ising.cpp.o.requires

CMakeFiles/single.dir/ising.cpp.o.provides: CMakeFiles/single.dir/ising.cpp.o.requires
	$(MAKE) -f CMakeFiles/single.dir/build.make CMakeFiles/single.dir/ising.cpp.o.provides.build
.PHONY : CMakeFiles/single.dir/ising.cpp.o.provides

CMakeFiles/single.dir/ising.cpp.o.provides.build: CMakeFiles/single.dir/ising.cpp.o

CMakeFiles/single.dir/single.cpp.o: CMakeFiles/single.dir/flags.make
CMakeFiles/single.dir/single.cpp.o: ../single.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/single.dir/single.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/single.dir/single.cpp.o -c /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/single.cpp

CMakeFiles/single.dir/single.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/single.dir/single.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/single.cpp > CMakeFiles/single.dir/single.cpp.i

CMakeFiles/single.dir/single.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/single.dir/single.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/single.cpp -o CMakeFiles/single.dir/single.cpp.s

CMakeFiles/single.dir/single.cpp.o.requires:
.PHONY : CMakeFiles/single.dir/single.cpp.o.requires

CMakeFiles/single.dir/single.cpp.o.provides: CMakeFiles/single.dir/single.cpp.o.requires
	$(MAKE) -f CMakeFiles/single.dir/build.make CMakeFiles/single.dir/single.cpp.o.provides.build
.PHONY : CMakeFiles/single.dir/single.cpp.o.provides

CMakeFiles/single.dir/single.cpp.o.provides.build: CMakeFiles/single.dir/single.cpp.o

# Object files for target single
single_OBJECTS = \
"CMakeFiles/single.dir/ising.cpp.o" \
"CMakeFiles/single.dir/single.cpp.o"

# External object files for target single
single_EXTERNAL_OBJECTS =

single: CMakeFiles/single.dir/ising.cpp.o
single: CMakeFiles/single.dir/single.cpp.o
single: CMakeFiles/single.dir/build.make
single: /usr/local/Cellar/open-mpi/1.6.2/lib/libmpi_cxx.dylib
single: /usr/local/Cellar/open-mpi/1.6.2/lib/libmpi.dylib
single: /usr/lib/libm.dylib
single: /usr/local/Cellar/hdf5/1.8.12/lib/libhdf5_hl.dylib
single: /usr/local/Cellar/hdf5/1.8.12/lib/libhdf5.dylib
single: /usr/local/lib/libsz.dylib
single: /usr/lib/libz.dylib
single: /usr/lib/libdl.dylib
single: /usr/lib/libm.dylib
single: /usr/local/Cellar/python/2.7.6/Frameworks/Python.framework/Versions/2.7/lib/python2.7/config/libpython2.7.a
single: /usr/local/Cellar/hdf5/1.8.12/lib/libhdf5_hl.dylib
single: /usr/local/Cellar/hdf5/1.8.12/lib/libhdf5.dylib
single: /usr/local/lib/libsz.dylib
single: /usr/lib/libz.dylib
single: /usr/lib/libdl.dylib
single: /usr/local/Cellar/python/2.7.6/Frameworks/Python.framework/Versions/2.7/lib/python2.7/config/libpython2.7.a
single: CMakeFiles/single.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable single"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/single.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/single.dir/build: single
.PHONY : CMakeFiles/single.dir/build

CMakeFiles/single.dir/requires: CMakeFiles/single.dir/ising.cpp.o.requires
CMakeFiles/single.dir/requires: CMakeFiles/single.dir/single.cpp.o.requires
.PHONY : CMakeFiles/single.dir/requires

CMakeFiles/single.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/single.dir/cmake_clean.cmake
.PHONY : CMakeFiles/single.dir/clean

CMakeFiles/single.dir/depend:
	cd /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/build /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/build /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/build/CMakeFiles/single.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/single.dir/depend
