#ifndef __RAY_H__
#define __RAY_H__

#include <glm/glm.hpp>

namespace raintrace
{
	class ray
	{
	public:
		ray(glm::vec4 point, glm::vec4 direction);
		
		const glm::vec4 point;
		const glm::vec4 direction;
	};
}

#endif