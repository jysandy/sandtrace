#include "ray.h"

namespace raintrace
{
	ray::ray(glm::vec4 point, glm::vec4 direction) :
	point(point), direction(glm::normalize(direction))
	{
	}
}