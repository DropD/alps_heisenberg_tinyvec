cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(ndim_spin NONE)

set(ALPS_ROOT_DIR /Users/ricoh/Applications/alps)

# find ALPS Library
find_package(ALPS REQUIRED PATHS ${ALPS_ROOT_DIR} $ENV{ALPS_HOME} NO_SYSTEM_ENVIRONMENT_PATH)
message(STATUS "Found ALPS: ${ALPS_ROOT_DIR} (revision: ${ALPS_VERSION})")
include(${ALPS_USE_FILE})

# enable C and C++ compilers
enable_language(C CXX)

# rule for generating single core heisenberg program
add_executable(prof_g3_s2_default prof_g3_s2_default.cpp)
target_link_libraries(prof_g3_s2_default ${ALPS_LIBRARIES})

add_executable(prof_g3_s2_oe prof_g3_s2_oe.cpp)
target_link_libraries(prof_g3_s2_oe ${ALPS_LIBRARIES})

add_executable(prof_g3_s3_default prof_g3_s3_default.cpp)
target_link_libraries(prof_g3_s3_default ${ALPS_LIBRARIES})

add_executable(prof_g3_s4_default prof_g3_s4_default.cpp)
target_link_libraries(prof_g3_s4_default ${ALPS_LIBRARIES})

add_executable(prof_g3_s4_oe prof_g3_s4_oe.cpp)
target_link_libraries(prof_g3_s4_oe ${ALPS_LIBRARIES})

add_executable(prof_g3_s4_oe4 prof_g3_s4_oe4.cpp)
target_link_libraries(prof_g3_s4_oe4 ${ALPS_LIBRARIES})

add_executable(prof_g3_s4_oe_sse prof_g3_s4_oe_sse.cpp)
target_link_libraries(prof_g3_s4_oe_sse ${ALPS_LIBRARIES})
 
#if (ALPS_HAVE_PYTHON)
#
#	# rule for generating python export
#	set_property(GLOBAL APPEND PROPERTY PY_MODULES_LIST ndsim_c)
#	if(BUILD_SHARED_LIBS)
#	    add_library(ndsim_c MODULE export.cpp)
#		set_target_properties(ndsim_c PROPERTIES COMPILE_DEFINITIONS "${ALPS_SHARED_CPPFLAGS}")
#		if(WIN32 AND NOT UNIX)
#			set_target_properties(ndsim_c PROPERTIES SUFFIX ".pyd")
#	    endif(WIN32 AND NOT UNIX)
#	else(BUILD_SHARED_LIBS)
#		set_property(GLOBAL APPEND PROPERTY PY_STATIC_MODULES_LIST ndsim_c)
#		add_library(ndsim_c STATIC export.cpp)
#	endif (BUILD_SHARED_LIBS)
#	set_target_properties(ndsim_c PROPERTIES PREFIX "")
#	target_link_libraries(ndsim_c ${ALPS_LIBRARIES})
#
#endif (ALPS_HAVE_PYTHON)
