cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(tinivec_bench NONE)

set(ALPS_ROOT_DIR /cluster/home/ricoh/local/)

include_directories(../nd_testing/)

option(Euler "sets flags for building on Euler if ON" OFF)

# find ALPS Library
find_package(ALPS REQUIRED PATHS ${ALPS_ROOT_DIR} $ENV{ALPS_HOME} NO_SYSTEM_ENVIRONMENT_PATH)
message(STATUS "Found ALPS: ${ALPS_ROOT_DIR} (revision: ${ALPS_VERSION})")
include(${ALPS_USE_FILE})

# enable C and C++ compilers
enable_language(C CXX)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${bench_flags}")
set(bench_flags "-march=native -mavx") 
if(Euler)
    set(euler_flags "-fabi-version=6")
else(Euler)
    set(euler_flags "")
endif(Euler)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${bench_flags} ${euler_flags}")

#  benchmark
add_executable(plus bench_plus.cpp)
target_link_libraries(plus ${ALPS_LIBRARIES})
add_executable(minus bench_minus.cpp)
target_link_libraries(minus ${ALPS_LIBRARIES})
add_executable(divide bench_divide.cpp)
target_link_libraries(divide ${ALPS_LIBRARIES})
add_executable(multiply bench_multiply.cpp)
target_link_libraries(multiply ${ALPS_LIBRARIES})

add_executable(btest btest.cpp)
target_link_libraries(btest ${ALPS_LIBRARIES})
