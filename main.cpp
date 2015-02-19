#include <chrono>
#include <iostream>
#include <future>
#include <vector>
#include <cmath>

#include <boost/lexical_cast.hpp>

#include "classes/image_data.h"
#include "classes/scene.h"
#include "helperfunctions.h"

int main(int argc, char** argv)
{
	using namespace sandtrace;
	namespace chrono = std::chrono;

	if (argc < 3)
	{
		std::cout << "Usage: sandtrace <width> <height>" << std::endl;
		return 1;
	}

	int render_width, render_height;
	try
	{
		render_width = boost::lexical_cast<int>(argv[1]);
		render_height = boost::lexical_cast<int>(argv[2]);
	}
	catch(const boost::bad_lexical_cast&)
	{
		std::cout << "Invalid dimensions" << std::endl;
		return 2;
	}

	std::cout << "Constructing scene...";
	auto sphere_scene = build_sphere_scene();
	std::cout << "done." << std::endl;

	std::cout << "Rendering..." << std::flush;
	auto begin_time = chrono::steady_clock::now();

	auto im_data = image_data{render_width, render_height};

	//Divide the columns of the image among various threads, and render in parallel.
	const int number_of_threads = 4;
	auto futures = std::vector<std::future<void>>{};
	auto render_task =
	[&](int start_col, int last_col)
	{
		for (int i = start_col; i < last_col; i++)
		{
			for (int j = 0; j < render_height; j++)
			{
				auto pixel_ray = build_ray(sphere_scene.cam, i, j, render_width, render_height);
				im_data(i, j) = ray_traced_color(pixel_ray, sphere_scene);
			}
		}
	};
	int cols_per_thread = std::ceil(static_cast<float>(render_width) / number_of_threads);
	//For each thread
	for (int i = 0; i < number_of_threads; i++)
	{
		int start_col = i * cols_per_thread;
		int end_col = start_col + cols_per_thread;
		if (end_col + number_of_threads >= render_width)
		{
			//If this thread is the last, then set the end row to the last row.
			end_col = render_width;
		}
		futures.push_back(std::async(std::launch::async, [=](){ render_task(start_col, end_col); }));
	}

	for (auto& f : futures)
	{
		f.get();
	}

	auto duration = chrono::steady_clock::now() - begin_time;
	std::cout << "done." << std::endl;

	auto hours = chrono::duration_cast<chrono::hours>(duration);
	auto minutes = chrono::duration_cast<chrono::minutes>(duration % chrono::hours(1));
	auto seconds = chrono::duration_cast<chrono::seconds>(duration % chrono::minutes(1));
	auto milliseconds = chrono::duration_cast<chrono::milliseconds>(duration % chrono::seconds(1));
	std::cout << "Rendering time: ";
	std::cout << hours.count() << ":" << minutes.count() << ":" << seconds.count()
		<< ":" << milliseconds.count() << std::endl;

	std::cout << "Saving to scene.jpg..." << std::flush;
	save_scene(im_data, "scene.jpg");
	std::cout << "done." << std::endl;

	return 0;
}
