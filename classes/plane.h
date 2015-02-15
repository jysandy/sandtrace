#ifndef __PLANE_H__
#define __PLANE_H__

#include <glm/glm.hpp>

#include "primitive.h"

namespace sandtrace
{
	class plane : public primitive
	{
	public:
		plane(glm::vec4 point, glm::vec4 normal, material mat);
		virtual ~plane(){}

		virtual bool try_intersects(const ray& r, glm::vec4& intersection);
		virtual glm::vec4 normal_at(glm::vec4 surface_point);

		glm::vec4 point;
		glm::vec4 normal;
	};
}

#endif
