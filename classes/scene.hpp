#ifndef __SANDTRACE_SCENE_H__
#define __SANDTRACE_SCENE_H__

#include <vector>
#include <list>
#include <memory>
#include <stdexcept>
#include <utility>

#include <fbxsdk.h>

#include "mesh.hpp"
#include "camera.hpp"
#include "primitive.hpp"
#include "directional_light.hpp"
#include "point_light.hpp"
#include "spot_light.hpp"
#include "texture_pool.hpp"

/*
 * Defines a 3D scene as a camera and a collection of primitives.
 */
namespace sandtrace
{
    class scene
    {
    public:
        typedef std::vector<std::shared_ptr<primitive>> primitive_vector;

        static scene from_fbx_file(std::string fbx_filename, std::string texname);
        static camera default_camera();
        static std::vector<directional_light> default_dlights();
        static std::vector<point_light> default_plights();
        static std::vector<spot_light> default_slights();

        primitive_vector primitives;
        std::list<mesh> meshes;
        camera cam;
        std::vector<directional_light> directional_lights;
        std::vector<point_light> point_lights;
        std::vector<spot_light> spot_lights;

    private:
        //Only from_fbx_file should be able to call this
        scene() : cam(scene::default_camera())
        {}

        void build_mesh_list(FbxNode* node, std::string texname);

        texture_pool texpool;
    };


}

#endif
