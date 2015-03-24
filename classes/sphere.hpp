#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <glm/glm.hpp>

#include "primitive.hpp"
#include "texture.hpp"

#include <cmath>
#include <algorithm>

namespace sandtrace
{
    class sphere : public primitive
    {
    public:
        sphere(glm::vec3 position, float radius, material mat);
        virtual ~sphere(){}

        virtual bool try_intersects(const ray& r, glm::vec3& intersection) const;
        virtual color_vertex vertex_at(glm::vec3 surface_point) const;
        virtual material mat() const;

        glm::vec3 position;
        float radius;
        material mat;
        texture tex;

    private:
        glm::vec2 texcoords_at(glm::vec3 surface_point) const;
    };
}

#endif
