#ifndef __SANDTRACE_SCENE_H__
#define __SANDTRACE_SCENE_H__

#include <vector>
#include <list>
#include <memory>
#include <stdexcept>
#include <utility>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "geometry/mesh.hpp"
#include "camera.hpp"
#include "geometry/primitive.hpp"
#include "lighting/directional_light.hpp"
#include "lighting/point_light.hpp"
#include "lighting/spot_light.hpp"
#include "textures/texture_pool.hpp"

/*
 * Defines a 3D scene as a camera and a collection of primitives.
 */
namespace sandtrace
{
    class scene
    {
    public:
        typedef std::vector<std::shared_ptr<primitive>> primitive_vector;

        scene(camera c, primitive_vector p,
            std::vector<directional_light> directional_lights,
            std::vector<point_light> point_lights,
            std::vector<spot_light> spot_lights
        );

        static camera default_camera();
        static std::vector<directional_light> default_dlights();
        static std::vector<point_light> default_plights();
        static std::vector<spot_light> default_slights();
        static scene from_json(std::string filename);

        primitive_vector primitives;
        std::list<mesh> meshes;
        camera cam;
        std::vector<directional_light> directional_lights;
        std::vector<point_light> point_lights;
        std::vector<spot_light> spot_lights;

    private:
        scene() : cam(scene::default_camera())
        {}

        texture_pool texpool;
    };


}

#endif
