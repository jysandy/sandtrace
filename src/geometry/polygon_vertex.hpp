#ifndef __POLYGON_VERTEX_H__
#define __POLYGON_VERTEX_H__

#include <glm/glm.hpp>

namespace sandtrace
{
    struct polygon_vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texcoord;
    };
}

#endif
