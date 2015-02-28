#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <array>

#include "polygon_vertex.hpp"
#include "ray.hpp"

namespace sandtrace
{
    class triangle
    {
    public:
        triangle(polygon_vertex a, polygon_vertex b, polygon_vertex c);

        bool try_intersects(const ray& in_ray, glm::vec3& intersection) const;
        polygon_vertex interpolated_point(glm::vec3 surface_point) const;

        std::array<polygon_vertex, 3> vertices;
    private:
        float area;
    };

    float triangle_area(glm::vec3 a, glm::vec3 b, glm::vec3 c);
}

#endif
