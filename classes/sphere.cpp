#include "sphere.h"

namespace raintrace
{
	sphere::sphere(glm::vec4 position, float radius, material mat) :
	primitive(mat), position(position), radius(radius)
	{
	}
}