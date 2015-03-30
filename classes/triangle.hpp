#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <array>
#include <memory>

#include "polygon_vertex.hpp"
#include "ray.hpp"
#include "texture.hpp"
#include "primitive.hpp"
#include "material.hpp"

namespace sandtrace
{
    //TODO: Implement try_intersects
    class triangle : public primitive
    {
    public:
        triangle(polygon_vertex a, polygon_vertex b, polygon_vertex c,
            std::shared_ptr<texture> tx, std::shared_ptr<material> m);
        ~triangle(){}
        bool try_intersects(const ray& in_ray, glm::vec3& intersection) const;
        virtual color_vertex vertex_at(glm::vec3 surface_point) const;
        virtual material mat() const;

        std::array<polygon_vertex, 3> vertices;
        std::shared_ptr<texture> tex;
        std::shared_ptr<material> mat_;
    private:
        float area;
    };

    float triangle_area(glm::vec3 a, glm::vec3 b, glm::vec3 c);
}

#endif
