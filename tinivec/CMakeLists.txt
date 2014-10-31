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
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${bench_flags}")

# += benchmark
add_executable(plus bench_run.cpp)
target_link_libraries(plus ${ALPS_LIBRARIES})
