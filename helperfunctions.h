#ifndef __RAINTRACE_HELPERFUNCTIONS_H__
#define __RAINTRACE_HELPERFUNCTIONS_H__

#include <glm/glm.hpp>

#include "classes/Scene.h"
#include "classes/Sphere.h"
#include "classes/Plane.h"

namespace raintrace
{
	/*
	 * Builds a scene with a sphere resting on a plane surface.
	 */
	Scene buildSphereScene();
}

#endif
