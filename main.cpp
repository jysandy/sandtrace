#include <string>

#include "classes/image_data.h"
#include "classes/scene.h"
#include "helperfunctions.h"

int main(int argc, char** argv)
{
	using namespace sandtrace;
	cout << "Rendering..." << endl;
	clock_t t1, t2;
	t1 = clock();
	auto scene = build_sphere_scene();

	const int render_width = 400;
	const int render_height = 400;

	auto im_data = image_data(render_width, render_height);
	for (int i = 0; i < render_width; i++)
	{
		for (int j = 0; j < render_height; j++)
		{
			auto ray = build_ray(scene.cam, i, j, render_width, render_height);
			im_data(i, j) = ray_traced_color(ray, scene);
		}
	}

	std::string filename = "scene.png";
	save_scene(im_data, filename);

	t2 = clock();
	cout << ((float)t2 - (float)t1)/ 1000 << endl;
}
