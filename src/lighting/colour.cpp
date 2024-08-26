#include "lighting/colour.hpp"
#include <algorithm>
#include <glm/glm.hpp>

namespace sandtrace
{
    glm::vec4 convert_to_gamma_space(const glm::vec4& in)
    {
        return glm::vec4{
            glm::pow(in.x, 1 / 2.2),
            glm::pow(in.y, 1 / 2.2),
            glm::pow(in.z, 1 / 2.2),
            in.w
        };
    }

    glm::vec4 convert_to_linear_space(const glm::vec4& in)
    {
        return glm::vec4{
            glm::pow(in.x, 2.2),
            glm::pow(in.y, 2.2),
            glm::pow(in.z, 2.2),
            in.w
        };
    }

    glm::vec4 reinhard_tonemap(glm::vec4 in)
    {
        return glm::vec4{
                 in.r / (in.r + 1),
                 in.g / (in.g + 1),
                 in.b / (in.b + 1),
                 in.a
        };
    }

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

    glm::vec4 componentwise_multiply(glm::vec4 a, glm::vec4 b)
    {
        return glm::vec4{
            a.x * b.x,
            a.y * b.y,
            a.z * b.z,
            a.w * b.w
        };
    }

    glm::vec4 componentwise_divide(glm::vec4 a, glm::vec4 b)
    {
        return glm::vec4{
            a.x / b.x,
            a.y / b.y,
            a.z / b.z,
            a.w / b.w
        };
    }

    glm::vec4 componentwise_add(glm::vec4 a, float scalar)
    {
        return glm::vec4{
            a.x + scalar,
            a.y + scalar,
            a.z + scalar,
            a.w + scalar
        };
    }

    glm::vec4 aces_tonemap(glm::vec4 in)
    {
        float a = 2.51f;
        float b = 0.03f;
        float c = 2.43f;
        float d = 0.59f;
        float e = 0.14f;

        return saturate(
            componentwise_divide(
                componentwise_multiply(
                    in,
                    componentwise_add(a * in, b)
                ),
                componentwise_add(
                    componentwise_multiply(
                        in,
                        componentwise_add(
                            c * in,
                            d
                        )
                    ),
                    e
                )
            )
        );
    }
}