project("Raintracer")

add_definitions(-std=c++14)
add_subdirectory(classes)
add_executable(raintracer *.cpp)
target_link_libraries(raintracer classes)
