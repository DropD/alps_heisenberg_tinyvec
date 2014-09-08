cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(tinivec_bench NONE)

set(ALPS_ROOT_DIR /opt/alps)

include_directories(../nd_testing/)

# find ALPS Library
find_package(ALPS REQUIRED PATHS ${ALPS_ROOT_DIR} $ENV{ALPS_HOME} NO_SYSTEM_ENVIRONMENT_PATH)
message(STATUS "Found ALPS: ${ALPS_ROOT_DIR} (revision: ${ALPS_VERSION})")
include(${ALPS_USE_FILE})

# enable C and C++ compilers
enable_language(C CXX)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${bench_flags}")
set(bench_flags "-march=native -mavx") 

# += benchmarks
# available only in clang 3.6:
# -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize"

## no optimization
### no march=native
add_executable(pb_no_i386 bench_run_noopt.cpp)
target_link_libraries(pb_no_i386 ${ALPS_LIBRARIES})

add_executable(pb_no_native bench_run_noopt.cpp)
target_link_libraries(pb_no_native ${ALPS_LIBRARIES})

### with march=native
get_target_property(temp pb_no_native COMPILE_FLAGS)
if(temp STREQUAL "temp-NOTFOUND")
    set(temp "")
else()
    set(temp "${temp}")
endif()
set(temp "${temp} ${bench_flags}")
set_target_properties(pb_no_native PROPERTIES COMPILE_FLAGS ${temp})

## template unroll
### no march=native
add_executable(pb_ur_i386 bench_run_ur.cpp)
target_link_libraries(pb_ur_i386 ${ALPS_LIBRARIES})

add_executable(pb_ur_native bench_run_ur.cpp)
target_link_libraries(pb_ur_native ${ALPS_LIBRARIES})

### with march=native
get_target_property(temp pb_ur_native COMPILE_FLAGS)
if(temp STREQUAL "temp-NOTFOUND")
    set(temp "")
else()
    set(temp "${temp}")
endif()
set(temp "${temp} ${bench_flags}")
set_target_properties(pb_ur_native PROPERTIES COMPILE_FLAGS ${temp})

## hand unroll
### no march=native
add_executable(pb_uh_i386 bench_run_urm.cpp)
target_link_libraries(pb_uh_i386 ${ALPS_LIBRARIES})

add_executable(pb_uh_native bench_run_urm.cpp)
target_link_libraries(pb_uh_native ${ALPS_LIBRARIES})

### with march=native
get_target_property(temp pb_uh_native COMPILE_FLAGS)
if(temp STREQUAL "temp-NOTFOUND")
    set(temp "")
else()
    set(temp "${temp}")
endif()
set(temp "${temp} ${bench_flags}")
set_target_properties(pb_uh_native PROPERTIES COMPILE_FLAGS ${temp})

## hand unrolled vectorized
### no march=native
### does not compile, obviously
# add_executable(pb_uv_i386 bench_run_urv.cpp)
# target_link_libraries(pb_uv_i386 ${ALPS_LIBRARIES})

add_executable(pb_uv_native bench_run_urv.cpp)
target_link_libraries(pb_uv_native ${ALPS_LIBRARIES})

### with march=native
get_target_property(temp pb_uv_native COMPILE_FLAGS)
if(temp STREQUAL "temp-NOTFOUND")
    set(temp "")
else()
    set(temp "${temp}")
endif()
set(temp "${temp} ${bench_flags}")
set_target_properties(pb_uv_native PROPERTIES COMPILE_FLAGS ${temp})
  
## verify vectorization result
add_executable(verify bench_verify.cpp)
target_link_libraries(verify ${ALPS_LIBRARIES})
 
### with march=native
get_target_property(temp verify COMPILE_FLAGS)
if(temp STREQUAL "temp-NOTFOUND")
    set(temp "")
else()
    set(temp "${temp}")
endif()
set(temp "${temp} ${bench_flags}")
set_target_properties(verify PROPERTIES COMPILE_FLAGS ${temp})

#---------- template unrolled vectorized ----------
  
## pb_tv_native vectorization result
add_executable(pb_tv_native bench_run_tv.cpp)
target_link_libraries(pb_tv_native ${ALPS_LIBRARIES})
 
### with march=native
get_target_property(temp pb_tv_native COMPILE_FLAGS)
if(temp STREQUAL "temp-NOTFOUND")
    set(temp "")
else()
    set(temp "${temp}")
endif()
set(temp "${temp} ${bench_flags}")
set_target_properties(pb_tv_native PROPERTIES COMPILE_FLAGS ${temp})
                                               
