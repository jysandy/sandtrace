#ifndef __RAINTRACE_SCENE_H__
#define __RAINTRACE_SCENE_H__

#include <vector>
#include <memory

#include "camera.h"
#include "primitive.h"

/*
 * Defines a 3D scene as a camera and a collection of primitives.
 */
namespace raintrace
{
	class scene
	{
	public:
		typedef std::vector<std::unique_ptr<primitive>> primitive_vector;
		
		scene(camera c, primitive_vector p);
		
		primitive_vector primitives;
		camera cam;
	};
}

#endif
