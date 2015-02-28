#ifndef __DIRECTIONAL_LIGHT_H__
#define __DIRECTIONAL_LIGHT_H__

#include <glm/glm.hpp>

namespace sandtrace
{
	class directional_light
	{
	public:
		directional_light(
			glm::vec4 ambient,
			glm::vec4 diffuse,
			glm::vec4 specular,
			glm::vec3 direction);

		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		glm::vec3 direction;
	};
}

#endif
