cmake_minimum_required(VERSION 3.28)

project("Sandtrace")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(glm CONFIG REQUIRED)
find_package(PNG REQUIRED)
find_package(Boost REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(sandtrace)
target_include_directories(sandtrace PRIVATE src/)
target_link_libraries(sandtrace PRIVATE
	glm::glm
	PNG::PNG
	Boost::boost
	nlohmann_json::nlohmann_json
)

target_sources(sandtrace PRIVATE
	"src/main.cpp"
	"src/renderer.cpp"
	"src/image_data.cpp")
	
target_sources(sandtrace PRIVATE
	"src/lighting/directional_light.cpp" 
	"src/lighting/spot_light.cpp" 
	"src/lighting/colour.cpp")

target_sources(sandtrace PRIVATE
	"src/geometry/plane.cpp"
	"src/geometry/sphere.cpp"
	"src/geometry/triangle.cpp")

target_sources(sandtrace PRIVATE
	"src/scene/camera.cpp"
	"src/scene/scene.cpp")

target_sources(sandtrace PRIVATE
	"src/textures/image_texture.cpp"
	"src/textures/texture_pool.cpp")