#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include "lighting/material.hpp"
#include "ray.hpp"
#include "color_vertex.hpp"

namespace sandtrace
{
    class primitive
    {
    public:
        virtual ~primitive(){}

        /*
         * Copies the intersection point into intersection if
         * r intersects the primitive.
         */
        virtual bool try_intersects(const ray& r, glm::vec3& intersection) const = 0;
        virtual color_vertex vertex_at(glm::vec3 surface_point) const = 0;
        virtual material mat() const = 0;
    };
}

#endif
