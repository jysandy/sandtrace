#ifndef __COLOR_VERTEX_H__
#define __COLOR_VERTEX_H__

#include <glm/glm.hpp>

namespace sandtrace
{
    struct color_vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec4 color;
    };
}

#endif
