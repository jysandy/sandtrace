#include <string>

#include "classes/image_data.h"
#include "classes/scene.h"
#include "helperfunctions.h"

int main(int agrc, char** argv)
{
	using namespace raintrace;
	
	auto scene = build_sphere_scene();
	
	const int render_width = 400;
	const int render_height = 400;
	
	auto im_data = image_data(render_width, render_height);
	for (int i = 0; i < render_width; i++)
	{
		for (int j = 0; j < render_height; j++)
		{
			auto ray = build_ray(scene.camera(), i, j, render_width, render_height);
			image_data[i][j] = ray_traced_color(ray, scene);
		}
	}
	
	std::string filename = "scene.png";
	save_scene(im_data, filename);
}
