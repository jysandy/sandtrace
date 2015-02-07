#include "plane.h"

namespace raintrace
{
	plane::plane(glm::vec4 point, glm::vec4 normal, material mat) :
	primitive(mat), point(point), normal(glm::normalize(normal))
	{
	}
}