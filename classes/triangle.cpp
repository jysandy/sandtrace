#include "triangle.hpp"

namespace sandtrace
{
    triangle::triangle(polygon_vertex a, polygon_vertex b, polygon_vertex c,
        std::shared_ptr<texture> tx, std::shared_ptr<material> m)
    : vertices{a, b, c}, tex(tx), mat_(m)
    {
        //Area of triangle is precomputed
        this->area = triangle_area(a.position, b.position, c.position);
    }

    color_vertex triangle::vertex_at(glm::vec3 surface_point) const
    {
        auto area0 = triangle_area(vertices[1].position, vertices[2].position, surface_point);
        auto area1 = triangle_area(vertices[0].position, vertices[2].position, surface_point);
        auto area2 = triangle_area(vertices[0].position, vertices[1].position, surface_point);
        auto point_normal = (area0 * vertices[0].normal
                            + area1 * vertices[1].normal
                            + area2 * vertices[2].normal) / this->area;
        auto point_texcoord = (area0 * vertices[0].texcoord
                              + area1 * vertices[1].texcoord
                              + area2 * vertices[2].texcoord) / this->area;
        auto point_color = this->tex->sample(point_texcoord);
        point_normal = glm::normalize(point_normal);

        return color_vertex{surface_point, point_normal, point_color};
    }

    material triangle::mat() const
    {
        return *(this->mat_);
    }

    float triangle_area(glm::vec3 a, glm::vec3 b, glm::vec3 c)
    {
        auto foo = glm::cross(b - a, c - a);
        return glm::length(foo) / 2.0f;
    }
}
