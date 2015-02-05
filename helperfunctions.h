#ifndef __RAINTRACE_HELPERFUNCTIONS_H__
#define __RAINTRACE_HELPERFUNCTIONS_H__

#include <glm/glm.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>


#include "classes/Scene.h"
#include "classes/Sphere.h"
#include "classes/Plane.h"
#include "classes/imageData.h"


namespace raintrace
{
	/*
	 * Builds a scene with a sphere resting on a plane surface.
	 */
	Scene buildSphereScene();
	
	/*
	 * Save the scene as a JPEG image.
	 */
	void save_scene();
}

#endif
