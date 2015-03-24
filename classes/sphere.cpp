#include "sphere.hpp"

namespace sandtrace
{
    sphere::sphere(glm::vec3 position, float radius, material mat) :
    mat(mat), position(position), radius(radius)
    {
    }

    bool sphere::try_intersects(const ray& r, glm::vec3& intersection) const
    {
        //Determining the coefficients of the quadratic equation
        auto foo = r.origin - this->position;
        //auto a = glm::dot(r.direction, r.direction);
        auto b = glm::dot(r.direction, foo);
        auto c = glm::length(foo) * glm::length(foo) - this->radius * this->radius;

        auto discriminant = b * b - c;

        if (discriminant < 0)
        {
            //The roots are either complex or real and equal. Ray doesn't intersect in these cases.
            return false;
        }

        //Roots
        auto x1 = (-b + glm::sqrt(discriminant));
        auto x2 = (-b - glm::sqrt(discriminant));

        if (std::abs(x1 - x2) < 0.0001)
        {
            return false;
        }

        if (x1 > 0 && x2 < 0)
        {
            intersection = r.origin + x1 * r.direction;
        }
        else if (x2 > 0 && x1 < 0)
        {
            intersection = r.origin + x2 * r.direction;
        }
        else if (x1 > 0 && x2 > 0)
        {
            //Choose the nearest intersection.
            intersection = r.origin + std::min(x1, x2) * r.direction;
        }
        else
        {
            //The sphere is behind the ray.
            return false;
        }

        return true;
    }

    color_vertex sphere::vertex_at(glm::vec3 surface_point) const
    {
        //For now the texcoords are dummies
        return color_vertex{
            surface_point,\
            glm::normalize(surface_point - this->position),
            tex.sample(texcoords_at(surface_point));
            };
    }

    material sphere::mat() const
    {
        return this->mat;
    }
}
