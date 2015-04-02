#ifndef __RAY_H__
#define __RAY_H__

#include <glm/glm.hpp>

namespace sandtrace
{
    class ray
    {
    public:
        ray(glm::vec3 origin, glm::vec3 direction);

        glm::vec3 origin;
        glm::vec3 direction;
    };
}

#endif
