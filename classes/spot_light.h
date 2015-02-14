#ifndef __SPOT_LIGHT_H__
#define __SPOT_LIGHT_H__

#include <glm/glm.hpp>

namespace sandtrace
{
	class spot_light
	{
	public:
		spot_light(
			glm::vec4 ambient,
			glm::vec4 diffuse,
			glm::vec4 specular,
			float a0, float a1, float a2,
			glm::vec4 position,
			float power);
		
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		float a0, a1, a2;	//Attenuation parameters
		glm::vec4 position;
		float power;
	};
}

#endif