#ifndef __DIRECTIONAL_LIGHT_H__
#define __DIRECTIONAL_LIGHT_H__

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>
#include "serdes/json.hpp"

namespace sandtrace
{
    class directional_light
    {
    public:
        directional_light(
            glm::vec4 ambient,
            glm::vec4 diffuse,
            glm::vec4 specular,
            glm::vec3 direction) :
            ambient(ambient), diffuse(diffuse), specular(specular), direction(glm::normalize(direction))
        {
        }

        directional_light() {}

        glm::vec4 ambient;
        glm::vec4 diffuse;
        glm::vec4 specular;
        glm::vec3 direction;
    };

    void from_json(const nlohmann::json& j, directional_light& d);
}

#endif
