#ifndef __SANDTRACE_IMAGE_TEXTURE_H__
#define __SANDTRACE_IMAGE_TEXTURE_H__

#include <string>

#include <glm/glm.hpp>
#include <boost/gil.hpp>
#include <boost/gil/extension/io/png.hpp>

#include "texture.hpp"

namespace sandtrace
{
    class image_texture : public texture
    {
    public:
        image_texture(std::string filename);
        virtual ~image_texture(){}

        virtual glm::vec4 sample(glm::vec2 texcoord) const;

    private:
        boost::gil::rgb8_image_t tex_image_;

    };

    int mod(int x, int n);
}

#endif
