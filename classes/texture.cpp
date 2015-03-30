#include "texture.hpp"

#include <cmath>

namespace sandtrace
{
    glm::vec4 texture::sample(glm::vec2 texcoord) const
    {
        namespace gil = boost::gil;
        //Point filtering
        int x = static_cast<int>(std::round(texcoord.x * tex_image.width()));
        int y = static_cast<int>(std::round(texcoord.y * tex_image.height()));

        //Wrap the texture coordinates.
        x = mod(x, tex_image.width());
        y = mod(y, tex_image.height());

        //Retrieve rgb values.
        auto image_view = gil::const_view(tex_image);
        auto pixel = image_view(x, y);
        glm::vec4 out;
        out.r = gil::get_color(pixel, gil::red_t());
        out.g = gil::get_color(pixel, gil::green_t());
        out.b = gil::get_color(pixel, gil::blue_t());
        out.a = gil::get_color(pixel, gil::alpha_t());

        return out;
    }

    int mod(int x, int n)
    {
        return (x % n + n) % n;
    }
}//namespace sandtrace
