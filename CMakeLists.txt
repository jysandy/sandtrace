cmake_minimum_required(VERSION 3.28)

project("Sandtrace")

#set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(classes)
file(GLOB sources *.cpp)
list(REMOVE_ITEM sources ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
find_package(glm CONFIG REQUIRED)
find_package(PNG REQUIRED)
find_package(Boost REQUIRED)

add_executable(sandtrace ${sources})
target_link_libraries(sandtrace PRIVATE 
	classes
	glm::glm
	PNG::PNG
	Boost::boost
)
