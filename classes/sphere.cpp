#include "sphere.h"

namespace sandtrace
{
	sphere::sphere(glm::vec4 position, float radius, material mat) :
	primitive(mat), position(position), radius(radius)
	{
	}
	
	virtual bool sphere::try_intersects(const ray& r, glm::vec4& intersection)
	{
		//Determining the coefficients of the quadratic equation
		auto foo = r.point - this->position;
		auto a = glm::dot(r.direction, r.direction);
		auto b = 2 * glm::dot(r.direction, foo);
		auto c = glm::dot(foo, foo) - this->radius * this->radius;
		
		auto discriminant = b * b - 4 * a * c;
		
		if (discriminant <= 0 || a == 0)
		{
			//The roots are either complex or real and equal. Ray doesn't intersect in these cases.
			//If a == 0 then something has gone terribly wrong -___-
			return false;
		}
		
		//Roots
		auto x1 = (-b + std::sqrt(discriminant)) / 2 * a;
		auto x2 = (-b - std::sqrt(discriminant)) / 2 * a;
		
		if (x1 < 0 || x2 < 0)
		{
			//Ray originates inside the sphere.
			intersection = r.point + std::max(x1, x2) * r.direction;
		}
		else
		{
			//Choose the nearest intersection.
			intersection = r.point + std::min(x1, x2) * r.direction;
		}
		
		return true;
	}
}