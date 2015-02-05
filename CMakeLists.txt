project("Raintracer")

add_definitions(-std=c++14)
include_directories(/usr/local/include)
add_subdirectory(classes)
add_executable(raintracer *.cpp)
target_link_libraries(raintracer classes)
