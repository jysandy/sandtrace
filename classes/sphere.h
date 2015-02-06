#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <glm/glm.hpp>

#include "primitive.h"

namespace raintrace
{
	class sphere : public primitive
	{
	public:
		sphere(glm::vec4 position, float radius, material mat);
	};
}

#endif
