#include "directional_light.hpp"

namespace sandtrace
{
	directional_light::directional_light(
		glm::vec4 ambient,
		glm::vec4 diffuse,
		glm::vec4 specular,
		glm::vec3 direction) : 
		ambient(ambient), diffuse(diffuse), specular(specular), direction(glm::normalize(direction))
	{
	}
}
