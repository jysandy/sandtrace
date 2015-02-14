#include "ray.h"

namespace sandtrace
{
	ray::ray(glm::vec4 point, glm::vec4 direction) :
	point(point), direction(glm::normalize(direction))
	{
	}
}