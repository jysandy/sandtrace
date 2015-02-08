#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <glm/glm.hpp>

#include "primitive.h"
#include <cmath>
#include <algorithm>

namespace raintrace
{
	class sphere : public primitive
	{
	public:
		sphere(glm::vec4 position, float radius, material mat);
		virtual ~sphere(){}
		
		virtual bool try_intersects(const ray& r, glm::vec4& intersection);
		
		glm::vec4 position;
		float radius;
	};
}

#endif
