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
include CMakeFiles/mpi.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mpi.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mpi.dir/flags.make

CMakeFiles/mpi.dir/ising.cpp.o: CMakeFiles/mpi.dir/flags.make
CMakeFiles/mpi.dir/ising.cpp.o: ../ising.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mpi.dir/ising.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mpi.dir/ising.cpp.o -c /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/ising.cpp

CMakeFiles/mpi.dir/ising.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mpi.dir/ising.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/ising.cpp > CMakeFiles/mpi.dir/ising.cpp.i

CMakeFiles/mpi.dir/ising.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mpi.dir/ising.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/ising.cpp -o CMakeFiles/mpi.dir/ising.cpp.s

CMakeFiles/mpi.dir/ising.cpp.o.requires:
.PHONY : CMakeFiles/mpi.dir/ising.cpp.o.requires

CMakeFiles/mpi.dir/ising.cpp.o.provides: CMakeFiles/mpi.dir/ising.cpp.o.requires
	$(MAKE) -f CMakeFiles/mpi.dir/build.make CMakeFiles/mpi.dir/ising.cpp.o.provides.build
.PHONY : CMakeFiles/mpi.dir/ising.cpp.o.provides

CMakeFiles/mpi.dir/ising.cpp.o.provides.build: CMakeFiles/mpi.dir/ising.cpp.o

CMakeFiles/mpi.dir/mpi.cpp.o: CMakeFiles/mpi.dir/flags.make
CMakeFiles/mpi.dir/mpi.cpp.o: ../mpi.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mpi.dir/mpi.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mpi.dir/mpi.cpp.o -c /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/mpi.cpp

CMakeFiles/mpi.dir/mpi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mpi.dir/mpi.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/mpi.cpp > CMakeFiles/mpi.dir/mpi.cpp.i

CMakeFiles/mpi.dir/mpi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mpi.dir/mpi.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/mpi.cpp -o CMakeFiles/mpi.dir/mpi.cpp.s

CMakeFiles/mpi.dir/mpi.cpp.o.requires:
.PHONY : CMakeFiles/mpi.dir/mpi.cpp.o.requires

CMakeFiles/mpi.dir/mpi.cpp.o.provides: CMakeFiles/mpi.dir/mpi.cpp.o.requires
	$(MAKE) -f CMakeFiles/mpi.dir/build.make CMakeFiles/mpi.dir/mpi.cpp.o.provides.build
.PHONY : CMakeFiles/mpi.dir/mpi.cpp.o.provides

CMakeFiles/mpi.dir/mpi.cpp.o.provides.build: CMakeFiles/mpi.dir/mpi.cpp.o

# Object files for target mpi
mpi_OBJECTS = \
"CMakeFiles/mpi.dir/ising.cpp.o" \
"CMakeFiles/mpi.dir/mpi.cpp.o"

# External object files for target mpi
mpi_EXTERNAL_OBJECTS =

mpi: CMakeFiles/mpi.dir/ising.cpp.o
mpi: CMakeFiles/mpi.dir/mpi.cpp.o
mpi: CMakeFiles/mpi.dir/build.make
mpi: /usr/local/Cellar/open-mpi/1.6.2/lib/libmpi_cxx.dylib
mpi: /usr/local/Cellar/open-mpi/1.6.2/lib/libmpi.dylib
mpi: /usr/lib/libm.dylib
mpi: /usr/local/Cellar/hdf5/1.8.12/lib/libhdf5_hl.dylib
mpi: /usr/local/Cellar/hdf5/1.8.12/lib/libhdf5.dylib
mpi: /usr/local/lib/libsz.dylib
mpi: /usr/lib/libz.dylib
mpi: /usr/lib/libdl.dylib
mpi: /usr/lib/libm.dylib
mpi: /usr/local/Cellar/python/2.7.6/Frameworks/Python.framework/Versions/2.7/lib/python2.7/config/libpython2.7.a
mpi: /usr/local/Cellar/hdf5/1.8.12/lib/libhdf5_hl.dylib
mpi: /usr/local/Cellar/hdf5/1.8.12/lib/libhdf5.dylib
mpi: /usr/local/lib/libsz.dylib
mpi: /usr/lib/libz.dylib
mpi: /usr/lib/libdl.dylib
mpi: /usr/local/Cellar/python/2.7.6/Frameworks/Python.framework/Versions/2.7/lib/python2.7/config/libpython2.7.a
mpi: CMakeFiles/mpi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable mpi"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mpi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mpi.dir/build: mpi
.PHONY : CMakeFiles/mpi.dir/build

CMakeFiles/mpi.dir/requires: CMakeFiles/mpi.dir/ising.cpp.o.requires
CMakeFiles/mpi.dir/requires: CMakeFiles/mpi.dir/mpi.cpp.o.requires
.PHONY : CMakeFiles/mpi.dir/requires

CMakeFiles/mpi.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mpi.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mpi.dir/clean

CMakeFiles/mpi.dir/depend:
	cd /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/build /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/build /Users/ricoh/Applications/alps-30-04-14/trunk/alps/tutorials/code-07-mcmain-mcbase/build/CMakeFiles/mpi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mpi.dir/depend

