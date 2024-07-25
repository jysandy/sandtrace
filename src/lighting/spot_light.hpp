#ifndef __SPOT_LIGHT_H__
#define __SPOT_LIGHT_H__

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

namespace sandtrace
{
    class spot_light
    {
    public:
        spot_light(
            glm::vec4 ambient,
            glm::vec4 diffuse,
            glm::vec4 specular,
            float brightness,
            float a1, float a2,
            glm::vec3 position,
            glm::vec3 direction,
            float power):
            ambient(ambient), diffuse(diffuse), specular(specular),
            brightness(brightness), a1(a1), a2(a2),
            position(position),
            direction(glm::normalize(direction)),
            power(power)
        {
        }

        spot_light() {}

        glm::vec4 ambient;
        glm::vec4 diffuse;
        glm::vec4 specular;
        float brightness, a1, a2;    //Attenuation parameters
        glm::vec3 position;
        glm::vec3 direction;
        float power;
    };

    void from_json(const nlohmann::json& j, spot_light& s);
}

#endif
