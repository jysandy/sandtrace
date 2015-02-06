#include "helperfunctions.h"

namespace raintrace
{
	scene build_sphere_scene()
	{
		auto primitives = scene::primitive_vector{};

		//Add the sphere
		auto sphere_position = glm::vec4{10, 10, -10, 1};
		auto sphere_radius = 6;
		primitives.push_back(std::make_unique<sphere>{sphere_position, sphere_radius});

		//Add the plane
		auto plane_point = glm::vec4{5, 0, -5, 1};
		auto plane_normal = glm::vec4{0, 1, 0, 0};
		primitives.push_back(std::make_unique<plane>{plane_point, plane_normal});
	}

	void save_scene(image_data img_data, string filename)
	{


	  auto view = boost::gil::planar_rgb_view(img_data.getWidth(), img_data.getHeight(), img_data.getR(), img_data.getG(), img_data.getB(), img_data.getWidth());

	  boost::gil::jpeg_write_view("scene.jpg", view);

	}

}


