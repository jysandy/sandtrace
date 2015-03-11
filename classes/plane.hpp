#ifndef __PLANE_H__
#define __PLANE_H__

#include <glm/glm.hpp>

#include "primitive.hpp"

namespace sandtrace
{
    class plane : public primitive
    {
    public:
        plane(glm::vec3 point, glm::vec3 normal, material mat);
        virtual ~plane(){}

        virtual bool try_intersects(const ray& r, glm::vec3& intersection) const;
        virtual polygon_vertex vertex_at(glm::vec3 surface_point) const;

        glm::vec3 point;
        glm::vec3 normal;
    };
}

#endif
