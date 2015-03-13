include_directories(/usr/local/include)
file(GLOB sources *.cpp)
add_definitions(-std=c++14)
add_library(classes ${sources})
