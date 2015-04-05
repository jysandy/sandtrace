#include "triangle.hpp"
#include <iostream>
namespace sandtrace
{
    triangle::triangle(polygon_vertex a, polygon_vertex b, polygon_vertex c,
        std::shared_ptr<texture> tx, std::shared_ptr<material> m)
    : vertices_{a, b, c}, tex_(tx), mat_(m)
    {
        //Area of triangle is precomputed
        this->area = triangle_area(a.position, b.position, c.position);
    }

    bool triangle::try_intersects(const ray& in_ray, glm::vec3& intersection) const
    {
        //Implements the Möller–Trumbore ray-triangle intersection algorithm,
        //as described at http://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
        intersection = glm::vec3(0);
        const float epsilon = 0.000001;

        auto e1 = vertices_[1].position - vertices_[0].position;
        auto e2 = vertices_[2].position - vertices_[0].position;

        auto p = glm::cross(in_ray.direction, e2);
        auto det = glm::dot(e1, p);

        if (std::abs(det) < epsilon )
        {
            return false;
        }
        auto inv_det = 1.0f / det;

        auto t = in_ray.origin - vertices_[0].position;
        auto u = glm::dot(t, p) * inv_det;
        if (u < 0.0f || u > 1.0f)
        {
            return false;
        }

        auto q = glm::cross(t, e1);
        auto v = glm::dot(in_ray.direction, q) * inv_det;
        if (v < 0.0f || u + v > 1.0f)
        {
            return false;
        }

        auto param = glm::dot(e2, q) * inv_det;
        if (param <= epsilon)
        {
            return false;
        }

        intersection = in_ray.origin + param * in_ray.direction;
        return true;
    }

    color_vertex triangle::vertex_at(glm::vec3 surface_point) const
    {
        auto area0 = triangle_area(vertices_[1].position, vertices_[2].position, surface_point);
        auto area1 = triangle_area(vertices_[0].position, vertices_[2].position, surface_point);
        auto area2 = triangle_area(vertices_[0].position, vertices_[1].position, surface_point);
        auto point_normal = (area0 * vertices_[0].normal
                            + area1 * vertices_[1].normal
                            + area2 * vertices_[2].normal) / this->area;
        auto point_texcoord = (area0 * vertices_[0].texcoord
                              + area1 * vertices_[1].texcoord
                              + area2 * vertices_[2].texcoord) / this->area;
        auto point_color = this->tex_->sample(point_texcoord);
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
