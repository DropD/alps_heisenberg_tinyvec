cmake_minimum_required(VERSION 2.8)

set(PYTHON_FRAMEWORK_DIR /usr/local/Frameworks/Python.framework/Versions/2.7)
set(PYTHON_SITE_PACKAGE_DIR ${PYTHON_FRAMEWORK_DIR}/lib/site-packages)
set(PYTHON_INCLUDE_DIRS ${PYTHON_FRAMEWORK_DIR}/include)

include(FindNumPy)
   
include_directories(
    BEFORE 
    /Users/ricoh/Applications/alps/include 
    /Users/ricoh/Applications/devel/boost/include
    ${PYTHON_INCLUDE_DIRS}
    ${NUMPY_INCLUDE_DIRS}
    )

add_executable(heisenberg main.cpp)
