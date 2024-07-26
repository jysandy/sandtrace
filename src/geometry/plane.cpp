#include "plane.hpp"
#include "serdes/json.hpp"

namespace sandtrace
{
    plane::plane(glm::vec3 point, glm::vec3 normal, material m, std::shared_ptr<texture> tx) :
    mat_(m), point(point), normal(glm::normalize(normal)), tex(tx)
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
            tex->sample(texcoords_at(surface_point))
            };
    }

    material plane::mat() const
    {
        return this->mat_;
    }

    glm::vec2 plane::texcoords_at(glm::vec3 surface_point) const
    {
        //TODO: This is a dummy. Replace with the real implementation.
        return glm::vec2(0, 0);
    }

    void from_json(const nlohmann::json& j, plane& p)
    {
        p.point  = vec_from_json<3>(j.at("point"));
        p.normal = glm::normalize(vec_from_json<3>(j.at("normal")));
        p.mat_   = j.at("material");
        p.tex    = j.at("texture");
    }
}
