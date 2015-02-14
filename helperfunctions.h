#ifndef __RAINTRACE_HELPERFUNCTIONS_H__
#define __RAINTRACE_HELPERFUNCTIONS_H__

#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>

#include "classes/scene.h"
#include "classes/sphere.h"
#include "classes/plane.h"
#include "classes/image_data.h"
#include "classes/camera.h"


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
	 * Save the scene as a JPEG image.
	 */
	void save_scene(image_data img_data, std::string filename);
}

#endif
