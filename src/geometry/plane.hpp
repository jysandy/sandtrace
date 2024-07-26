#ifndef __PLANE_H__
#define __PLANE_H__

#include <memory>

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

#include "primitive.hpp"
#include "textures/texture.hpp"
#include "color_vertex.hpp"
#include "lighting/material.hpp"

namespace sandtrace
{
    class plane : public primitive
    {
    public:
        plane(glm::vec3 point, glm::vec3 normal, material m, std::shared_ptr<texture> tx);
        plane() {}
        virtual ~plane(){}

        virtual bool try_intersects(const ray& r, glm::vec3& intersection) const;
        virtual color_vertex vertex_at(glm::vec3 surface_point) const;
        virtual material mat() const;

        glm::vec3 point;
        glm::vec3 normal;
        material mat_;
        std::shared_ptr<texture> tex;

    private:
        glm::vec2 texcoords_at(glm::vec3 surface_point) const;
    };

    void from_json(const nlohmann::json& j, plane& p);
}

#endif
