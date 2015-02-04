#include <string>

#include "classes/ImageData.h"
#include "classes/Scene.h"
#include "helperfunctions.h"

int main(int agrc, char** argv)
{
	using namespace raintrace;
	
	auto scene = buildSphereScene();
	
	const int renderWidth = 400;
	const int renderHeight = 400;
	
	auto image_data = ImageData(renderWidth, renderHeight);
	for (int i = 0; i < renderHeight; i++)
	{
		for (int j = 0; j < renderWidth; j++)
		{
			auto ray = buildRay(scene.getCamera(), i, j, renderWidth, renderHeight);
			image_data[i][j] = ray_traced_color(ray, scene);
		}
	}
	
	std::string filename = "scene.png";
	save_scene(image_data, filename);
}
