#ifndef __PLANE_H__
#define __PLANE_H__

#include <glm/glm.hpp>

#include "primitive.h"

namespace raintrace
{
	class plane : public primitive
	{
	public:
		plane(glm::vec4 point, glm::vec4 normal, material mat);
		virtual ~plane(){}
		
		virtual bool try_intersects(const ray& r, glm::vec4& intersection);
		
		glm::vec4 point;
		glm::vec4 normal;
	};
}

#endif
