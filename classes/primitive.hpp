#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include "material.hpp"
#include "ray.hpp"

namespace sandtrace
{
	class primitive
	{
	public:
		primitive(material mat);
		virtual ~primitive(){}

		/*
		 * Copies the intersection point into intersection if
		 * r intersects the primitive.
		 */
		virtual bool try_intersects(const ray& r, glm::vec3& intersection) = 0;
		virtual glm::vec3 normal_at(glm::vec3 surface_point) = 0;

		material mat;


	};
}

#endif
