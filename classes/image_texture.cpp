#include "image_texture.hpp"
#include <cmath>

namespace sandtrace
{
    image_texture::image_texture(std::string filename)
    {
        namespace gil = boost::gil;
        gil::png_read_image(filename, tex_image_);
    }

    glm::vec4 image_texture::sample(glm::vec2 texcoord) const
    {
        namespace gil = boost::gil;
        //Point filtering
        int x = static_cast<int>(std::round(texcoord.x * tex_image_.width()));
        int y = static_cast<int>(std::round(texcoord.y * tex_image_.height()));

        //Wrap the texture coordinates.
        x = mod(x, tex_image_.width());
        y = mod(y, tex_image_.height());

        //Retrieve rgb values.
        auto image_view = gil::const_view(tex_image_);
        auto pixel = image_view(x, y);
        glm::vec4 out;
        out.r = gil::get_color(pixel, gil::red_t()) / 255.0f;
        out.g = gil::get_color(pixel, gil::green_t()) / 255.0f;
        out.b = gil::get_color(pixel, gil::blue_t()) / 255.0f;
        //out.a = gil::get_color(pixel, gil::alpha_t());
        out.a = 1.0f;

        return out;
    }

    int mod(int x, int n)
    {
        return (x % n + n) % n;
    }
}
