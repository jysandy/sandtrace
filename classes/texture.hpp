#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <glm/glm.hpp>

namespace sandtrace
{
    class texture
    {
    public:
        virtual glm::vec4 sample(glm::vec2 texcoord) const = 0;
    };
}

#endif
