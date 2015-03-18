#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <array>
#include <memory>

#include "polygon_vertex.hpp"
#include "ray.hpp"
#include "mesh.hpp"

namespace sandtrace
{
    //TODO: Implement try_intersects
    class triangle
    {
    public:
        triangle(){}
        triangle(polygon_vertex a, polygon_vertex b, polygon_vertex c, std::shared_ptr<mesh> parent);
        ~triangle(){}
        bool try_intersects(const ray& in_ray, glm::vec3& intersection) const;
        virtual polygon_vertex vertex_at(glm::vec3 surface_point) const;

        std::array<polygon_vertex, 3> vertices;
        std::weak_ptr<mesh> parent_mesh;

    private:
        float area;
    };

    float triangle_area(glm::vec3 a, glm::vec3 b, glm::vec3 c);
}

#endif
