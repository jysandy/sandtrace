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

	ray build_ray(const camera& cam, int i, int j, int render_width, int render_height)
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

	intersection_data nearest_intersection(const ray& r, const scene::primitive_vector& primitives)
	{
		scene::primitive_vector::value_type closest_primitive;
		glm::vec4 closest_intersection;
		auto closest_distance = std::max<float>();
		bool intersects = false;
		for (auto p : primitives)
		{
			glm::vec4 intersection;
			if (p->try_intersects(r, intersection))
			{
				intersects = true;
				auto distance = glm::length(intersection - r.origin);
				if (distance < closest_distance)
				{
					closest_distance = distance;
					closest_intersection = intersection;
					closest_primitive = p;
				}
			}
		}

		intersection_data idata;

		if (!intersects)
		{
			idata.intersects = false;
			return idata;
		}

		idata.intersects = true;
		idata.mat = closest_primitive->mat;
		idata.intersection_point = closest_intersection;
		idata.normal = closest_primitive->normal_at(closest_intersection);

		return idata;
	}

	glm::vec4 phong_color(const ray& eye_to_point, const intersection_data& intersection, const scene& target_scene)
	{
		auto dcolor = directional_phong_color(eye_to_point, intersection, target_scene);
		auto pcolor = point_phong_color(eye_to_point, intersection, target_scene);
		auto scolor = spot_phong_color(eye_to_point, intersection, target_scene);

		auto final_color = dcolor + pcolor + scolor;
		return glm::clamp(final_color, 0.0, 1.0);
	}

	glm::vec4 directional_phong_color(const ray& eye_to_point, const intersection_data& idata, const scene& target_scene)
	{
		auto final_color = glm::vec4{0, 0, 0, 1};

		for (auto dlight : target_scene.directional_lights)
		{
			final_color += dlight.ambient * idata.mat.ambient;

			//For a directional light, the shadow ray is simply the negative
			//of the light's direction.
			auto light_vector = -dlight.direction;
			auto shadow_ray = ray{idata.intersection_point, glm::normalize(light_vector)};
			if (is_blocked(shadow_ray, target_scene.primitives))
			{
				continue;
			}
			light_vector = glm::normalize(light_vector);

			//Diffuse component
			auto kd = std::max(glm::dot(light_vector, idata.normal), 0);
			final_color += kd * dlight.diffuse * idata.mat.diffuse;

			if (kd > 0)
			{
				//Specular component
				auto reflected_ray = glm::reflect(-shadow_ray, idata.normal);
				auto ks = std::max(glm::dot(reflected_ray, -eye_to_point.direction));
				ks = glm::pow(ks, idata.mat.shininess);
				final_color += ks * dlight.specular * idata.mat.specular;
			}
		}

		return final_color;
	}

	glm::vec4 point_phong_color(const ray& eye_to_point, const intersection_data& idata, const scene& target_scene)
	{
		auto final_color = glm::vec4{0, 0, 0, 1};

		for (auto plight : target_scene.point_lights)
		{
			final_color += plight.ambient * idata.mat.ambient;

			//Here the shadow ray is the ray from the point of intersection to the light.
			auto light_vector = plight.position - idata.intersection_point;
			auto shadow_ray = ray{idata.intersection_point, glm::normalize(light_vector)};
			if (is_blocked(shadow_ray, target_scene.primitives, plight.position))
			{
				continue;
			}

			auto d = glm::length(light_vector);
			light_vector = glm::normalize(light_vector);
			auto attenuation_factor = 1.0f / (plight.a0 + plight.a1 * d + plight.a2 * d * d);

			//Diffuse component
			auto kd = std::max(glm::dot(light_vector, idata.normal), 0);
			final_color += kd * dlight.diffuse * idata.mat.diffuse * attenuation_factor;

			if (kd > 0)
			{
				//Specular component
				auto ref = glm::reflect(-light_vector, idata.normal);
				auto ks = std::max(glm::dot(ref, -eye_to_point.direction), 0);
				ks = glm::pow(ks, idata.mat.shininess);
				final_color += ks * dlight.specular * idata.mat.specular * attenuation_factor;
			}
		}

		return final_color;
	}

	glm::vec4 spot_phong_color(const ray& eye_to_point, const intersection_data& idata, const scene& target_scene)
	{
		auto final_color = glm::vec4{0, 0, 0, 1};

		for (auto slight : target_scene.spot_lights)
		{
			final_color += slight.ambient * idata.mat.ambient;

			auto light_vector = slight.position - idata.intersection_point;
			auto shadow_ray = ray{idata.intersection_point, glm::normalize(light_vector)};

			auto d = glm::length(light_vector);
			light_vector = glm::normalize(light_vector);
			auto attenuation_factor = 1.0f / (slight.a0 + slight.a1 * d + slight.a2 * d * d);
			auto intensity_factor = glm::pow(std::max(glm::dot(-light_vector, slight.direction), 0), slight.power);

			//Diffuse component
			auto kd = std::max(glm::dot(light_vector, idata.normal), 0);
			final_color += kd * slight.diffuse * idata.mat.diffuse * attenuation_factor * intensity_factor;

			if (kd > 0)
			{
				//Specular component
				auto ref = glm::reflect(-light_vector, idata.normal);
				auto ks = std::max(glm::dot(ref, -eye_to_point.direction), 0);
				ks = glm::pow(ks, idata.mat.shininess);
				final_color += ks * slight.specular * idata.mat.specular * attenuation_factor * intensity_factor;
			}
		}

		return final_color;
	}

	bool is_blocked(const ray& r, const scene::primitive_vector& primitives)
	{
		for (auto p : primitives)
		{
			glm::vec4 intersection;
			if (p->try_intersects(r, intersection))
			{
				return true;
			}
		}

		return false;
	}

	bool is_blocked(const ray& r, const scene::primitive_vector& primitives, const glm::vec4& limit)
	{
		for (auto p : primitives)
		{
			glm::vec4 intersection;
			if (p->try_intersects(r, intersection))
			{
				auto max_length = glm::length(limit - r.origin);
				auto length = glm::length(intersection - r.origin);
				if (length < max_length)
				{
					return true;
				}
			}
		}

		return false;
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
