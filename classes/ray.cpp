#include "ray.h"

namespace sandtrace
{
	ray::ray(glm::vec4 origin, glm::vec4 direction) :
	origin(origin), direction(glm::normalize(direction))
	{
	}
}
