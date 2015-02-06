#ifndef __RAINTRACE_HELPERFUNCTIONS_H__
#define __RAINTRACE_HELPERFUNCTIONS_H__

#include <glm/glm.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>
#include <memory>


#include "classes/scene.h"
#include "classes/sphere.h"
#include "classes/plane.h"
#include "classes/image_data.h"


namespace raintrace
{
	/*
	 * Builds a scene with a sphere resting on a plane surface.
	 */
	scene build_sphere_scene();

	/*
	 * Save the scene as a JPEG image.
	 */
	void save_scene(image_data img_data, string filename);
}

#endif
