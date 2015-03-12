cmake_minimum_required(VERSION 2.8)

project("Sandtrace")

#set(CMAKE_VERBOSE_MAKEFILE on)
add_definitions(-std=c++14)
include_directories(/usr/local/include)
add_subdirectory(classes)
file(GLOB sources *.cpp)
list(REMOVE_ITEM sources ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
find_library(LIBJPEG libjpeg.a)
find_library(PROGRAM_OPTIONS libboost_program_options.a)
add_executable(sandtrace ${sources})
target_link_libraries(sandtrace -pthread classes ${LIBJPEG} ${PROGRAM_OPTIONS})

find_library(BOOST_TEST libboost_unit_test_framework.a)
add_executable(test test.cpp helperfunctions.cpp)
target_link_libraries(test -pthread classes ${BOOST_TEST} ${LIBJPEG})
