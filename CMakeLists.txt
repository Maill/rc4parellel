cmake_minimum_required(VERSION 3.12)
project(rc4parallel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -Wall -g -fdiagnostics-color=auto -fmax-errors=2 -std=c++11 -lpthread")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -fmax-errors=2")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

set(CMAKE_CXX_STANDARD 11)

set(SOURCES_FILES src/main.cpp src/RC4.cpp src/RC4.h)

add_executable(rc4parallel ${SOURCES_FILES})