#include <chrono>
#include <iostream>

#include "classes/image_data.h"
#include "classes/scene.h"
#include "helperfunctions.h"

int main(int argc, char** argv)
{
	using namespace sandtrace;
	namespace chrono = std::chrono;

	std::cout << "Constructing scene...";
	auto sphere_scene = build_sphere_scene();
	std::cout << "done." << std::endl;

	std::cout << "Rendering..." << std::flush;
	auto begin_time = chrono::steady_clock::now();
	const int render_width = 600;
	const int render_height = 600;

	auto im_data = image_data{render_width, render_height};
	for (int i = 0; i < render_width; i++)
	{
		for (int j = 0; j < render_height; j++)
		{
			auto pixel_ray = build_ray(sphere_scene.cam, i, j, render_width, render_height);
			im_data(i, j) = ray_traced_color(pixel_ray, sphere_scene);
		}
	}
	auto duration = begin_time - chrono::steady_clock::now();
	std::cout << "done." << std::endl;

	auto hours = chrono::duration_cast<chrono::hours>(duration);
	auto minutes = chrono::duration_cast<chrono::minutes>(duration % chrono::hours(1));
	auto seconds = chrono::duration_cast<chrono::seconds>(duration % chrono::minutes(1));
	std::cout << "Rendering time: ";
	std::cout << hours.count() << ":" << minutes.count() << ":" << seconds.count() << std::endl;

	std::cout << "Saving to scene.jpg...";
	save_scene(im_data, "scene.jpg");
	std::cout << "done." << std::endl;

	return 0;
}
