#include "material.hpp"

namespace sandtrace
{
	material::material()
	{
		
	}

	material::material(
		glm::vec4 diffuse,
		glm::vec4 ambient,
		glm::vec4 specular,
		float shininess,
		float reflectance):
		diffuse(diffuse), ambient(ambient), specular(specular), shininess(shininess), reflectance(reflectance)
		{
		}
}
