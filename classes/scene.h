#ifndef __RAINTRACE_SCENE_H__
#define __RAINTRACE_SCENE_H__

#include <vector>
#include <memory

#include "camera.h"
#include "primitive.h"
#include "directional_light.h"
#include "point_light.h"
#include "spot_light.h"

/*
 * Defines a 3D scene as a camera and a collection of primitives.
 */
namespace sandtrace
{
	class scene
	{
	public:
		typedef std::vector<std::shared_ptr<primitive>> primitive_vector;

		scene(camera c, primitive_vector p,
			std::vector<directional_light> directional_lights,
			std::vector<point_light> point_lights,
			std::vector<spot_light> spot_lights
		);

		primitive_vector primitives;
		camera cam;
		std::vector<directional_light> directional_lights;
		std::vector<point_light> point_lights;
		std::vector<spot_light> spot_lights;
	};
}

#endif
