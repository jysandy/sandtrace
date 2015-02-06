include_directories(/usr/local/include)
file(GLOB sources ./*.cpp)
add_library(classes ${sources})
