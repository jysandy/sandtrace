#ifndef __RAY_H__
#define __RAY_H__

#include <glm/glm.hpp>

namespace sandtrace
{
    class ray
    {
    public:
        ray(const glm::vec3& origin, const glm::vec3& direction)
        : origin(origin), direction(glm::normalize(direction))
        {
        }

        glm::vec3 origin;
        glm::vec3 direction;
    };
}

#endif
