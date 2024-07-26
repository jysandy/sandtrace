#include "scene.hpp"
#include "serdes/json.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

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


    scene::scene(camera c, 
        std::vector<sphere> spheres,
        std::vector<plane> planes,
        std::vector<directional_light> directional_lights,
        std::vector<point_light> point_lights,
        std::vector<spot_light> spot_lights) :
        cam(c), spheres(spheres), planes(planes),
        directional_lights(directional_lights),
        point_lights(point_lights),
        spot_lights(spot_lights)
    {
    }

    scene scene::from_json(std::string filename)
    {
        using json = nlohmann::json;
        std::ifstream f(filename);

        if (f.fail())
        {
            throw std::runtime_error("Couldn't open scene file");
        }

        auto scene_data = json::parse(f);
        auto the_scene = scene();
        

        // TODO: Validate that (look_at - look_from) and up are not parallel/antiparallel
        the_scene.cam.look_from = vec_from_json<3>(scene_data["camera"]["look_from"]);
        the_scene.cam.look_at   = vec_from_json<3>(scene_data["camera"]["look_at"]);
        the_scene.cam.up        = vec_from_json<3>(scene_data["camera"]["up"]);
        the_scene.cam.fov       = glm::radians(scene_data["camera"]["fov_degrees"].template get<float>());

        the_scene.directional_lights = 
            scene_data.value("directional_lights", std::vector<directional_light>{});
        the_scene.spot_lights =
            scene_data.value("spot_lights", std::vector<spot_light>{});
        the_scene.point_lights =
            scene_data.value("point_lights", std::vector<point_light>{});
        the_scene.spheres =
            scene_data.value("spheres", std::vector<sphere>{});
        the_scene.planes =
            scene_data.value("planes", std::vector<plane>{});

        return the_scene;
    }
}
