#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <glm/glm.hpp>

#include "primitive.h"
#include <cmath>
#include <algorithm>

namespace sandtrace
{
	class sphere : public primitive
	{
	public:
		sphere(glm::vec4 position, float radius, material mat);
		virtual ~sphere(){}

		virtual bool try_intersects(const ray& r, glm::vec4& intersection);
		virtual glm::vec4 normal_at(glm::vec4 surface_point);

		glm::vec4 position;
		float radius;
	};
}

#endif
