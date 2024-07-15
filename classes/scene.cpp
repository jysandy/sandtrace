#include "scene.hpp"
#include <iostream>

namespace sandtrace
{
    camera scene::default_camera()
    {
        //(look_from - look_at) cross up must not be a null vector!!!
        auto look_from = glm::vec3(150.0f, 30.0f, 0.0f);
        auto look_at = glm::vec3(0.0f, 0.0f, 0.0f);
        auto up = glm::vec3(0, 1, 0);
        auto fov = glm::half_pi<float>();

        return camera(look_from, look_at, up, fov);
    }

    std::vector<directional_light> scene::default_dlights()
    {
        //Two directional lights.

        auto ambient = glm::vec4(0.1, 0.1, 0.1, 1.0);
        auto diffuse = glm::vec4(0.7, 0.7, 0.7, 1.0);
        auto specular = glm::vec4(0.2, 0.2, 0.2, 1.0);

        auto direction1 = glm::vec3(1, -1, 1);
        auto direction2 = glm::vec3(-1, -1, -1);

        return std::vector<directional_light>{
            {ambient, diffuse, specular, direction1},
            {ambient, diffuse, specular, direction2}
        };
    }

    std::vector<point_light> scene::default_plights()
    {
        //No point lights.
        return std::vector<point_light>();
    }

    std::vector<spot_light> scene::default_slights()
    {
        //No spot lights.
        return std::vector<spot_light>();
    }


    scene::scene(camera c, scene::primitive_vector p,
        std::vector<directional_light> directional_lights,
        std::vector<point_light> point_lights,
        std::vector<spot_light> spot_lights) :
        cam(c), primitives(p),
        directional_lights(directional_lights),
        point_lights(point_lights),
        spot_lights(spot_lights)
    {
    }

}
