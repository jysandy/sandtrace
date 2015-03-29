#include "plane.hpp"

namespace sandtrace
{
    plane::plane(glm::vec3 point, glm::vec3 normal, material mat, std::string texname) :
    primitive(mat), point(point), normal(glm::normalize(normal)), tex(texname)
    {
    }

    bool plane::try_intersects(const ray& r, glm::vec3& intersection) const
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

    color_vertex plane::vertex_at(glm::vec3 surface_point) const
    {
        return color_vertex{
            surface_point,
            this->normal,
            tex.sample(texcoords_at(surface_point))
            };
    }

    material plane::mat() const
    {
        return this->mat;
    }

    glm::vec2 plane::texcoords_at(glm::vec3 surface_point)
    {
        //TODO: This is a dummy. Replace with the real implementation.
        return glm::vec2(0, 0)
    }
}
