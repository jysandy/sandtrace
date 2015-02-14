#ifndef __RAY_H__
#define __RAY_H__

#include <glm/glm.hpp>

namespace sandtrace
{
	class ray
	{
	public:
		ray(glm::vec4 origin, glm::vec4 direction);

		glm::vec4 origin;
		glm::vec4 direction;
	};
}

#endif
