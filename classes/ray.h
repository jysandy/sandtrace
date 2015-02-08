#ifndef __RAY_H__
#define __RAY_H__

#include <glm/glm.hpp>

namespace raintrace
{
	class ray
	{
	public:
		ray(glm::vec4 point, glm::vec4 direction);
		
		glm::vec4 point;
		glm::vec4 direction;
	};
}

#endif