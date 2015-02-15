#ifndef __RAINTRACE_HELPERFUNCTIONS_H__
#define __RAINTRACE_HELPERFUNCTIONS_H__

#include <memory>
#include <string>
#include <vector>
#include <stack>
#include <limits>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>

#include "classes/scene.h"
#include "classes/sphere.h"
#include "classes/plane.h"
#include "classes/image_data.h"
#include "classes/camera.h"
#include "classes/primitive.h"
#include "classes/material.h"


namespace sandtrace
{
	/*
	 * Builds a scene with a sphere resting on a plane surface.
	 */
	scene build_sphere_scene();

	/*
	 * Generates a ray from the camera to the pixel at (i, j) in the image plane.
	 */
	 ray build_ray(const camera& cam, int i, int j, int render_width, int render_height);

	/*
	 * Returns a traced ray's color.
	 */
	glm::vec4 ray_traced_color(const ray& pixel_ray, const scene& target_scene);

	/*
	 * Returned by nearest_intersection (see below)
	 */
	struct intersection_data
	{
		bool intersects;
		material mat;
		glm::vec4 intersection_point;
		glm::vec4 normal;
	};

	/*
	 * Returns data of the closest primitive which intersects the given ray.
	 */
	intersection_data nearest_intersection(const ray& r, const scene::primitive_vector& primitives);

	/*
	 * Applies the Phong model to compute the color at the intersection point.
	 */
	glm::vec4 phong_color(const ray& eye_to_point, const intersection_data& intersection, const scene& scene);

	/*
	 * Save the scene as a JPEG image.
	 */
	void save_scene(image_data img_data, std::string filename);
}

#endif
