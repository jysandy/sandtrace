#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>

#include <glm/glm.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_io.hpp>

namespace sandtrace
{
    class texture
    {
    public:
        texture(std::string filename);

        glm::vec4 sample(glm::vec2 texcoord) const;

    private:
        boost::gil::rgba8_image_t tex_image_;
    };

    int mod(int x, int n);
}

#endif
