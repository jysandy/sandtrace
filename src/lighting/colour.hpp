#ifndef __SANDTRACE_LIGHTING_COLOUR_HPP__
#define __SANDTRACE_LIGHTING_COLOUR_HPP__

#include <glm/glm.hpp>

namespace sandtrace
{
    glm::vec4 saturate(glm::vec4 in);
    glm::vec4 convert_to_gamma_space(const glm::vec4& in);
    glm::vec4 convert_to_linear_space(const glm::vec4& in);
    glm::vec4 aces_tonemap(glm::vec4 in);
    glm::vec4 reinhard_tonemap(glm::vec4 in);
}

#endif // !__SANDTRACE_LIGHTING_COLOUR_HPP__
