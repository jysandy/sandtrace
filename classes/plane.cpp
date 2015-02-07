#include "plane.h"

namespace raintrace
{
	plane::plane(glm::vec4 point, glm::vec4 normal, material mat) :
	primitive(mat), point(point), normal(glm::normalize(normal))
	{
	}
	
	virtual bool plane::try_intersects(ray r, glm::vec4& intersection)
	{
		auto denominator = glm::dot(r.direction, this->normal);
		if (denominator == 0)
		{
			//Ray is parallel to the plane. Doesn't intersect.
			return false;
		}
		
		auto t = glm::dot(this->point - r.point) / denominator;
		
		if (t < 0)
		{
			//Plane is behind the ray. Doesn't intersect.
			return false;
		}
		
		intersection = r.point + t * r.direction;
		return true;
	}
}