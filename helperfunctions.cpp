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
		primitives.push_back(std::make_shared<sphere>{sphere_position, sphere_radius, sphere_mat});

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
		primitives.push_back(std::make_shared<plane>{plane_point, plane_normal});

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

	ray	build_ray(const camera& cam, int i, int j, int render_width, int render_height)
	{
		auto alpha = glm::tan(cam.fov / 2f) * ((j - (render_width / 2f)) / (render_width / 2f) );
		auto beta = glm::tan(cam.fov / 2f) * (((render_height / 2f) - i) / (render_height / 2f) );

		//Form a left-handed orthonormal basis. Camera looks down the +w direction.
		auto w = glm::normalize(cam.look_at - cam.look_from);
		auto u = glm::normalize(glm::cross(w, cam.up));
		auto v = glm::normalize (glm::cross(u, w));

		return ray{cam.look_from, alpha * u + beta * v + w};
	}

	glm::vec4 ray_traced_color(const ray& pixel_ray, const scene& target_scene)
	{
		const glm::vec4 empty_color{0.0, 0.0, 0.0, 1.0};
		const int max_stack_depth = 3;

		//The recursive ray-tracing is performed iteratively, using a stack.
		struct stack_entry
		{
			glm::vec4 color;
			float reflectance;

			stack_entry(glm::vec4 c, float r) : color(c), reflectance(r) {}
		};
		std::stack<const stack_entry> recursion_stack;
		auto current_ray = pixel_ray;
		//This prevents the stack from ending up empty,
		//if the ray intersected no primitive.
		recursion_stack.emplace(empty_color, 1);

		while (recursion_stack.size() < max_stack_depth + 1)
		{
			auto data = nearest_intersection(pixel_ray, target_scene.primitives);
			if (!data.intersects)
			{
				//If the ray did not intersect any primitive
				recursion_stack.emplace(empty_color, 0);
				break;
			}

			auto color = phong_color(current_ray, data, target_scene);
			recursion_stack.emplace(color, data.mat.reflectance);
			current_ray = glm::reflect(current_ray, data.normal);
		}

		glm::vec4 final_color = recursion_stack.top();
		recursion_stack.pop();

		while (!recursion_stack.empty())
		{
			auto entry = stack.top();
			stack.pop();
			final_color = entry.color + entry.reflectance * final_color;
		}

		return final_color;
	}

	void save_scene(image_data img_data, std::string filename)
	{
		using namespace boost::gil = gil;

		auto target_image = gil::rgb8_image_t{img_data.render_width, image_data.render_height};
		auto target_image_view = gil::view{target_image};

		for (int x = 0; x < target_image_view.width(); x++)
		{
			for (int y = 0; i < target_image_view.height(); y++)
			{
				//Mapping the color values of img_data, which are floats in [0, 1],
				//into integers in [0, 255].
				gil::get_color(target_image_view(x, y), gil::red_t()) = static_cast<int>(img_data(x, y).r * 255);
				gil::get_color(target_image_view(x, y), gil::green_t()) = static_cast<int>(img_data(x, y).g * 255);
				gil::get_color(target_image_view(x, y), gil::blue_t()) = static_cast<int>(img_data(x, y).b * 255);
			}
		}

		gil::jpeg_write_view(filename, target_image_view);
	}
}
