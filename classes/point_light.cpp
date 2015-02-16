#include "point_light.h"

namespace sandtrace
{
	point_light::point_light(
		glm::vec4 ambient,
		glm::vec4 diffuse,
		glm::vec4 specular,
		float a0, float a1, float a2,
		glm::vec3 position):
		ambient(ambient), diffuse(diffuse), specular(specular),
		a0(a0), a1(a1), a2(a2),
		position(position)
	{
	}
}
