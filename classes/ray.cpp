#include "ray.h"

namespace sandtrace
{
	ray::ray(glm::vec3 origin, glm::vec3 direction) :
	origin(origin), direction(glm::normalize(direction))
	{
	}
}
