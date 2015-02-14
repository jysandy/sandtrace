#include "helperfunctions.h"

namespace sandtrace
{
	scene build_sphere_scene()
	{
		auto primitives = scene::primitive_vector{};

		//Add the sphere
		auto sphere_position = glm::vec4{10, 10, -10, 1};
		auto sphere_radius = 6;
		auto sphere_colour = glm::vec4
		{
			0xF2 / 255f,
			0xA3 / 255f,
			0xA3 / 255f,
			1
		};//A light pinkish colour
		auto sphere_mat = material
		{
			sphere_colour,
			sphere_colour,
			sphere_colour,
			8,
			0.3
		};//Rather dull, doesn't reflect/bleed much colour
		primitives.push_back(std::make_unique<sphere>{sphere_position, sphere_radius, sphere_mat});

		//Add the plane
		auto plane_point = glm::vec4{5, 0, -5, 1};
		auto plane_normal = glm::vec4{0, 1, 0, 0};
		auto plane_colour = glm::vec4
		{
			0xDA / 255f,
			0xDA / 255f,
			0xDA / 255f,
			1
		};//A silvery-grey colour
		auto plane_mat = material
		{
			plane_colour,
			plane_colour,
			plane_colour,
			64,
			0.8
		};//Shiny, mirror-like surface
		primitives.push_back(std::make_unique<plane>{plane_point, plane_normal});

		//Build the camera
		//Positioning the camera to look at the sphere from slightly above
		auto look_from = glm::vec4{10, 12, 0, 1};
		auto look_at = sphere_position;
		auto up = glm::vec4{0, 1, 0, 0};
		float fov = glm::quarter_pi<float>();
		auto cam = camera{look_from, look_at, up, fov};

		//Build just one directional light
		auto ambient = glm::vec4(0.1, 0.1, 0.1, 1.0);
		auto diffuse = glm::vec4(0.7, 0.7, 0.7, 1.0);
		auto specular = glm::vec4(0.2, 0.2, 0.2, 1.0);
		auto direction = glm::vec4(1, -1, 1, 0);
		auto dlights = std::vector<directional_light>
		{
			directional_light{ambient, diffuse, specular, direction}
		};

		return scene
		{
			cam, primitives, dlights,
			std::vector<point_light>{},
			std::vector<spot_light>{}
		};
	}

	//TODO: Verify this formula
	ray	build_ray(const camera& cam, int i, int j, int render_width, int render_height)
	{

		auto alpha = glm::tan(cam.fov / 2f) * ((j - (render_width / 2f)) / render_width / 2f ));
		auto beta = glm::tan(cam.fov / 2f) * (((render_height / 2f) - i) / render_height / 2f ));

		return ray{cam.look_from, glm::vec4(alpha, beta, -1.0, 0.0)};
	}
}
