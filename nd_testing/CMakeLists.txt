cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(ndim_spin NONE)

set(ALPS_ROOT_DIR /opt/alps)

# find ALPS Library
find_package(ALPS REQUIRED PATHS ${ALPS_ROOT_DIR} $ENV{ALPS_HOME} NO_SYSTEM_ENVIRONMENT_PATH)
message(STATUS "Found ALPS: ${ALPS_ROOT_DIR} (revision: ${ALPS_VERSION})")
include(${ALPS_USE_FILE})

# enable C and C++ compilers
enable_language(C CXX)

set(bench_flags "-march=native -mavx") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${bench_flags}")

# += benchmarks
# available only in clang 3.6:
# -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize"

add_executable(plus_default plus_default.cpp)
target_link_libraries(plus_default ${ALPS_LIBRARIES})

get_target_property(temp plus_default COMPILE_FLAGS)
if(temp STREQUAL "temp-NOTFOUND")
    set(temp "")
else()
    set(temp "${temp}")
endif()
set(temp "${temp} ${bench_flags}")
set_target_properties(plus_default PROPERTIES COMPILE_FLAGS ${temp})

add_executable(plus_unroll plus_unroll.cpp)
target_link_libraries(plus_unroll ${ALPS_LIBRARIES})

get_target_property(temp plus_unroll COMPILE_FLAGS)
if(temp STREQUAL "temp-NOTFOUND")
    set(temp "")
else()
    set(temp "${temp}")
endif()
set(temp "${temp} ${bench_flags}")
set_target_properties(plus_unroll PROPERTIES COMPILE_FLAGS ${temp})

add_executable(prof_g3_s2_oe prof_g3_s2_oe.cpp)
target_link_libraries(prof_g3_s2_oe ${ALPS_LIBRARIES})

add_executable(prof_g3_s2_oe_sse prof_g3_s2_oe_sse.cpp)
target_link_libraries(prof_g3_s2_oe_sse ${ALPS_LIBRARIES})

add_executable(prof_g3_s3_default prof_g3_s3_default.cpp)
target_link_libraries(prof_g3_s3_default ${ALPS_LIBRARIES})

add_executable(prof_g3_s4_default prof_g3_s4_default.cpp)
target_link_libraries(prof_g3_s4_default ${ALPS_LIBRARIES})

add_executable(prof_g3_s4_oe prof_g3_s4_oe.cpp)
target_link_libraries(prof_g3_s4_oe ${ALPS_LIBRARIES})

add_executable(prof_g3_s4_oe4 prof_g3_s4_oe4.cpp)
target_link_libraries(prof_g3_s4_oe4 ${ALPS_LIBRARIES})

add_executable(prof_g3_s4_unroll prof_g3_s4_unroll.cpp)
target_link_libraries(prof_g3_s4_unroll ${ALPS_LIBRARIES})

add_executable(prof_g3_s4_oe_sse prof_g3_s4_oe_sse.cpp)
target_link_libraries(prof_g3_s4_oe_sse ${ALPS_LIBRARIES})

add_executable(prof_g3_s4_oe4_avx EXCLUDE_FROM_ALL prof_g3_s4_oe4_avx.cpp)
target_link_libraries(prof_g3_s4_oe4_avx ${ALPS_LIBRARIES})

get_target_property(temp prof_g3_s4_oe4_avx COMPILE_FLAGS)
if(temp STREQUAL "temp-NOTFOUND")
    set(temp "")
else()
    set(temp "${temp}")
endif()
set(temp "${temp} -mavx")
set_target_properties(prof_g3_s4_oe4_avx PROPERTIES COMPILE_FLAGS ${temp})

add_executable(prof_g3_s4_unroll_avx EXCLUDE_FROM_ALL prof_g3_s4_unroll_avx.cpp)
target_link_libraries(prof_g3_s4_unroll_avx ${ALPS_LIBRARIES})

get_target_property(temp prof_g3_s4_unroll_avx COMPILE_FLAGS)
if(temp STREQUAL "temp-NOTFOUND")
    set(temp "")
else()
    set(temp "${temp}")
endif()
set(temp "${temp} -mavx")
set_target_properties(prof_g3_s4_unroll_avx PROPERTIES COMPILE_FLAGS ${temp})
  
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
