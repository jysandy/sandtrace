cmake_minimum_required(VERSION 2.8)

project("Sandtrace")

add_definitions(-std=c++14)
include_directories(/usr/local/include)
add_subdirectory(classes)
file(GLOB sources ./*.cpp)
find_library(libs "jpeg")
add_executable(sandtrace ${sources})
target_link_libraries(sandtrace classes ${libs})
