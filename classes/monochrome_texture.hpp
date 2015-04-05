#ifndef __SANDTRACE_MONOCHROME_TEXTURE__
#define __SANDTRACE_MONOCHROME_TEXTURE__

#include <glm/glm.hpp>

#include "texture.hpp"

namespace sandtrace
{
    class monochrome_texture : public texture
    {
    public:
        monochrome_texture(glm::vec4 c) : color_(c){}
        virtual ~monochrome_texture(){}

        virtual glm::vec4 sample(glm::vec2 texcoord) const
        {
            return color_;
        }

    private:
        glm::vec4 color_;
    };
}

#endif
