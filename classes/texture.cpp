#include "texture.h"

#include <cmath>

namespace sandtrace
{
    glm::vec4 sample(glm::vec2 texcoord)
    {
        namespace gil = boost::gil;
        //Biliniear filtering
        int x = static_cast<int>(std::round(texcoord.x * tex_image.width()));
        int y = static_cast<int>(std::round(texcoord.y * tex_image.height()));

        //Wrap the texture coordinates.
        x = mod(x, tex_image.width());
        y = mod(y, tex_image.height());

        glm::vec4 out;
        //Retrieve rgb values.
        auto image_view = gil::view(tex_image);
        auto pixel = image_view[x][y];
        out.r = gil::get_color<gil::red_t>(pixel);
        out.g = gil::get_color<gil::green_t>(pixel);
        out.b = gil::get_color<gil::blue_t>(pixel);
        out.a = gil::get_color<gil::alpha_t>(pixel);

        return out;
    }

    int mod(int x, int n)
    {
        return (x % n + n) % n;
    }
}//namespace sandtrace
