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
	};
}

#endif
