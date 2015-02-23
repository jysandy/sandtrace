cmake_minimum_required(VERSION 2.8)

project("Sandtrace")

#set(CMAKE_VERBOSE_MAKEFILE on)
add_definitions(-std=c++14)
include_directories(/usr/local/include)
add_subdirectory(classes)
file(GLOB sources ./*.cpp)
find_library(LIBJPEG libjpeg.a)
find_library(PROGRAM_OPTIONS libboost_program_options.a)
add_executable(sandtrace ${sources})
target_link_libraries(sandtrace -pthread classes ${LIBJPEG} ${PROGRAM_OPTIONS})
