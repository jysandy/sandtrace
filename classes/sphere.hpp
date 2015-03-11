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

		virtual bool try_intersects(const ray& r, glm::vec3& intersection) const;
		virtual polygon_vertex vertex_at(glm::vec3 surface_point) const;

		glm::vec3 position;
		float radius;
	};
}

#endif
