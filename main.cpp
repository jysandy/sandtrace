#include <chrono>

#include "classes/image_data.h"
#include "classes/scene.h"
#include "helperfunctions.h"

int main(int argc, char** argv)
{
	using namespace sandtrace;
	using namespace std::chrono = chrono;

	std::cout << "Constructing scene...";
	auto scene = build_sphere_scene();
	std::cout << "done." << std::endl;

	std::cout << "Rendering...";
	auto begin_time = chrono::steady_clock::now();
	const int render_width = 400;
	const int render_height = 400;

	auto im_data = image_data{render_width, render_height};
	for (int i = 0; i < render_width; i++)
	{
		for (int j = 0; j < render_height; j++)
		{
			auto ray = build_ray(scene.cam, i, j, render_width, render_height);
			im_data(i, j) = ray_traced_color(ray, scene);
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
