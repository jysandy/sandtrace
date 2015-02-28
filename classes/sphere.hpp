#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <glm/glm.hpp>

#include "primitive.hpp"
#include <cmath>
#include <algorithm>

namespace sandtrace
{
	class sphere : public primitive
	{
	public:
		sphere(glm::vec3 position, float radius, material mat);
		virtual ~sphere(){}

		virtual bool try_intersects(const ray& r, glm::vec3& intersection);
		virtual glm::vec3 normal_at(glm::vec3 surface_point);

		glm::vec3 position;
		float radius;
	};
}

#endif
