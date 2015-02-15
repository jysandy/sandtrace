#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include "material.h"
#include "ray.h"

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
		virtual bool try_intersects(const ray& r, glm::vec4& intersection) = 0;
		virtual glm::vec4 normal_at(glm::vec4 surface_point) = 0;

		material mat;


	};
}

#endif
