#include <chrono>
#include <iostream>
#include <cmath>
#include <nlohmann/json.hpp>
#include <cxxopts.hpp>

#include "image_data.hpp"
#include "scene/scene.hpp"
#include "renderer.hpp"

int main(int argc, char** argv)
{
	using namespace sandtrace;
	namespace chrono = std::chrono;

	cxxopts::Options options("sandtrace", "A recursive ray tracer");
	options.add_options()
		("s,scene", "Scene file", cxxopts::value<std::string>())
		("t,threads", "Number of threads", cxxopts::value<int>()->default_value("4"))
		("o,output", "Output file", cxxopts::value<std::string>()->default_value("scene.png"))
		;

	try
	{
		auto parsed_options = options.parse(argc, argv);

		int render_width, render_height;
		render_width = render_height = 1500;

		std::cout << "Constructing scene..." << std::flush;
		auto sphere_scene = scene::from_json(parsed_options["scene"].as<std::string>());
		sphere_scene.primitives = build_sphere_primitives();
		std::cout << "done." << std::endl;

		int number_of_threads = parsed_options["threads"].as<int>();
		std::cout << "Rendering..." << std::flush;
		auto begin_time = chrono::steady_clock::now();
		//Render!!
		auto im_data = render_image(render_width, render_height, sphere_scene, number_of_threads);
		auto duration = chrono::steady_clock::now() - begin_time;
		std::cout << "done." << std::endl;

		auto hours = chrono::duration_cast<chrono::hours>(duration);
		auto minutes = chrono::duration_cast<chrono::minutes>(duration % chrono::hours(1));
		auto seconds = chrono::duration_cast<chrono::seconds>(duration % chrono::minutes(1));
		auto milliseconds = chrono::duration_cast<chrono::milliseconds>(duration % chrono::seconds(1));
		std::cout << "Rendering time: ";
		std::cout << hours.count() << ":" << minutes.count() << ":" << seconds.count()
			<< ":" << milliseconds.count() << std::endl;

		std::string filename = parsed_options["output"].as<std::string>();
		std::cout << "Saving to " + filename + "..." << std::flush;
		save_scene(im_data, filename);
		std::cout << "done." << std::endl;

		return 0;
	}
	catch (const nlohmann::json::exception& e)
	{
		std::cerr << "Error parsing json!" << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (const cxxopts::exceptions::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}
