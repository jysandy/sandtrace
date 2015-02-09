#include "helperfunctions.h"

namespace raintrace
{
	scene build_sphere_scene()
	{
		auto primitives = scene::primitive_vector{};

		//Add the sphere
		auto sphere_position = glm::vec4{10, 10, -10, 1};
		auto sphere_radius = 6;
		auto sphere_colour = glm::vec4{
			0xF2 / 255f,
			0xA3 / 255f,
			0xA3 / 255f,
			1
		};//A light pinkish colour
		auto sphere_mat = material{
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
		auto plane_colour = glm::vec4{
			0xDA / 255f,
			0xDA / 255f,
			0xDA / 255f,
			1
		};//A silvery-grey colour
		auto plane_mat = material{
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

	void save_scene(image_data img_data, string filename)
	{


	  auto view = boost::gil::planar_rgb_view(img_data.getWidth(), img_data.getHeight(), img_data.getR(), img_data.getG(), img_data.getB(), img_data.getWidth());

	  boost::gil::jpeg_write_view("scene.jpg", view);

	}

	int winningObjectIndex(vector<double> object_intersections) {
		// return the index of the winning intersection
		int index_of_minimum_value;
		
		// prevent unnessary calculations
		if (object_intersections.size() == 0) {
			// if there are no intersections
			return -1;
		}
		else if (object_intersections.size() == 1) {
			if (object_intersections.at(0) > 0) {
				// if that intersection is greater than zero then its our index of minimum value
				return 0;
			}
			else {
				// otherwise the only intersection value is negative
				return -1;
			}
		}
		else {
			// otherwise there is more than one intersection
			// first find the maximum value
			
			double max = 0;
			for (int i = 0; i < object_intersections.size(); i++) {
				if (max < object_intersections.at(i)) {
					max = object_intersections.at(i);
				}
			}
			
			// then starting from the maximum value find the minimum positive value
			if (max > 0) {
				// we only want positive intersections
				for (int index = 0; index < object_intersections.size(); index++) {
					if (object_intersections.at(index) > 0 && object_intersections.at(index) <= max) {
						max = object_intersections.at(index);
						index_of_minimum_value = index;
					}
				}
				
				return index_of_minimum_value;
			}
			else {
				// all the intersections were negative
				return -1;
			}
		}
	}
}


