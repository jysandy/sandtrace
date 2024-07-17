#include "lighting/colour.hpp"
#include <algorithm>
#include <glm/glm.hpp>

namespace sandtrace
{
    glm::vec4 saturate(glm::vec4 in)
    {
        using std::max;
        auto greatest = max(max(in.x, in.y), in.z);
        glm::vec4 out = in;
        if (greatest > 1)
        {
            out.x /= greatest;
            out.y /= greatest;
            out.z /= greatest;
        }

        if (out.w > 1)
        {
            out.w = 1;
        }

        return out;
    }
}