cmake_minimum_required(VERSION 2.8)

project("Raintrace")

add_definitions(-std=c++1y)
include_directories(/usr/local/include)
add_subdirectory(classes)
file(GLOB sources ./*.cpp)
add_executable(raintracer ${sources})
target_link_libraries(raintracer classes)
