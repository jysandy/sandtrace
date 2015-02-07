include_directories(/usr/local/include)
file(GLOB sources ./*.cpp)
add_definitions(-std=c++1y)
add_library(classes ${sources})
