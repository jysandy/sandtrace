#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <cmath>
#include <algorithm>
#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "primitive.hpp"
#include "textures/texture.hpp"
#include "lighting/material.hpp"


namespace sandtrace
{
    class sphere : public primitive
    {
    public:
        sphere(glm::vec3 position, float radius, material m, std::shared_ptr<texture> tx);
        virtual ~sphere(){}

        virtual bool try_intersects(const ray& r, glm::vec3& intersection) const;
        virtual color_vertex vertex_at(glm::vec3 surface_point) const;
        virtual material mat() const;

        glm::vec3 position;
        float radius;
        material mat_;
        std::shared_ptr<texture> tex;

    private:
        glm::vec2 texcoords_at(glm::vec3 surface_point) const;
        glm::vec3 normal_at(glm::vec3 surface_point) const;
    };
}

#endif
