#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <glm/glm.hpp>

namespace sandtrace
{
    class material
    {
    public:
        material(
            glm::vec4 ambient,
            glm::vec4 diffuse,
            glm::vec4 specular,
            float shininess,
            float reflectance):
            diffuse(diffuse), ambient(ambient), specular(specular), shininess(shininess), reflectance(reflectance)
            {
            }

        glm::vec4 diffuse;
        glm::vec4 ambient;
        glm::vec4 specular;
        float shininess;
        float reflectance;
    };
}

#endif
