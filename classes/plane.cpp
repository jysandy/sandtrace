#include "plane.h"

namespace sandtrace
{
	plane::plane(glm::vec3 point, glm::vec3 normal, material mat) :
	primitive(mat), point(point), normal(glm::normalize(normal))
	{
	}

	bool plane::try_intersects(const ray& r, glm::vec3& intersection)
	{
		auto denominator = glm::dot(r.direction, this->normal);
		if (denominator == 0)
		{
			//Ray is parallel to the plane. Doesn't intersect.
			return false;
		}

		auto t = glm::dot(this->point - r.origin, this->normal) / denominator;

		if (t <= 0)
		{
			//Plane is behind the ray. Doesn't intersect.
			return false;
		}

		intersection = r.origin + t * r.direction;
		return true;
	}

	glm::vec3 plane::normal_at(glm::vec3 surface_point)
	{
		return this->normal;
	}
}
