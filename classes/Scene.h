#ifndef __RAINTRACE_SCENE_H__
#define __RAINTRACE_SCENE_H__

#include <vector>
#include <memory

#include "Camera.h"
#include "Primitive.h"

/*
 * Defines a 3D scene as a camera and a collection of primitives.
 */
namespace raintrace
{
	class Scene
	{
	public:
		typedef std::vector<std::unique_ptr<Primitive>> PrimitiveVector;
		
		Scene(Camera c, PrimitiveVector p);
		
		const Camera& getCamera() const;
		const PrimitiveVector& getPrimitives() const;
		
	private:
		PrimitiveVector primitives;
		Camera camera;
	};
}

#endif
