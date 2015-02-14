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
		
		/*
		 * Copies the intersection point into intersection if
		 * r intersects the primitive.
		 */
		virtual bool try_intersects(const ray& r, glm::vec4& intersection) = 0;
		
		material mat;
		
		
	};
}

#endif
