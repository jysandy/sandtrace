#ifndef __RAINTRACE_HELPERFUNCTIONS_H__
#define __RAINTRACE_HELPERFUNCTIONS_H__

#include <memory>
#include <string>
#include <vector>
#include <stack>
#include <limits>
#include <algorithm>

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
	 * Used for thresholding in adaptive depth control.
	 */
	bool operator<=(const glm::vec4& left, const glm::vec4& right);

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
		glm::vec3 intersection_point;
		glm::vec3 normal;
	};

	/*
	 * Returns data of the closest primitive which intersects the given ray.
	 */
	intersection_data nearest_intersection(const ray& r, const scene::primitive_vector& primitives);

	/*
	 * Applies the Phong model to compute the color at the intersection point.
	 */
	glm::vec4 phong_color(const ray& eye_to_point, const intersection_data& intersection, const scene& target_scene);

	/*
	 * Computes the contribution of directional lights in the scene to the final color.
	 */
	glm::vec4 directional_phong_color(const ray& eye_to_point, const intersection_data& idata, const scene& target_scene);

	/*
	 * Computes the contribution of point lights in the scene to the final color.
	 */
	glm::vec4 point_phong_color(const ray& eye_to_point, const intersection_data& idata, const scene& target_scene);

	/*
	 * Computes the contribution of spot lights in the scene to the final color.
	 */
	glm::vec4 spot_phong_color(const ray& eye_to_point, const intersection_data& idata, const scene& target_scene);

	/*
	 * Tests if the ray intersects ANY primitive.
	 */
	bool is_blocked(const ray& r, const scene::primitive_vector& primitives);

	/*
	 * Tests if the ray is blocked at any point between its origin and the limit.
	 */
	bool is_blocked(const ray& r, const scene::primitive_vector& primitives, const glm::vec3& limit);

	/*
	 * Saturates a colour, preserving the RGB proportions.
	 */
	glm::vec4 saturate(glm::vec4 in);

	/*
	 * Save the scene as a JPEG image.
	 */
	void save_scene(image_data img_data, std::string filename);
}

#endif
