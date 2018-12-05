cmake_minimum_required(VERSION 3.8)
project(rc4parallel)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -fdiagnostics-color=auto -std=c++11 -lpthread")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")


set(SOURCES_FILES src/main.cpp src/RC4.h src/Functions.h src/Functions.cpp src/RC4.cpp test/MD5.cpp test/MD5.h)
set(LIBRC4_SOURCES_FILES ${CMAKE_CURRENT_LIST_DIR}/src/RC4.h ${CMAKE_CURRENT_LIST_DIR}/src/Functions.h ${CMAKE_CURRENT_LIST_DIR}/src/Functions.cpp ${CMAKE_CURRENT_LIST_DIR}/src/RC4.cpp)


add_executable(rc4parallel ${SOURCES_FILES})

#UNIT TESTS
enable_testing()
add_subdirectory(lib/googletest)

configure_file(${CMAKE_CURRENT_LIST_DIR}/data/1_input
        ${CMAKE_CURRENT_BINARY_DIR}/data/1_input COPYONLY)

configure_file(${CMAKE_CURRENT_LIST_DIR}/data/3_input
        ${CMAKE_CURRENT_BINARY_DIR}/data/3_input COPYONLY)

configure_file(${CMAKE_CURRENT_LIST_DIR}/data/5_input.jpg
        ${CMAKE_CURRENT_BINARY_DIR}/data/5_input.jpg COPYONLY)


add_subdirectory(test)


# Benchmark
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
add_subdirectory(lib/benchmark)

add_subdirectory(benchmark)