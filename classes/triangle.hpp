#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <array>

#include "primitive.hpp"
#include "polygon_vertex.hpp"

namespace sandtrace
{
    class triangle : public primitive
    {
    public:
        std::array<polygon_vertex, 3> vertices;

        virtual bool try_intersects(const ray& r, glm::vec3& intersection);
        virtual glm::vec3 normal_at(glm::vec3 surface_point);
    };
}

#endif
