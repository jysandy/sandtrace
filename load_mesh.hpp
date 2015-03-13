#ifndef __SANDTRACE_LOAD_MESH_H__
#define __SANDTRACE_LOAD_MESH_H__

#include <fbxsdk.h>

#include <glm/glm.hpp>

#include <list>
#include <exception>
#include <stdexcept>
#include <utility>
#include <string>

#include "classes/mesh.hpp"
#include "classes/material.hpp"

namespace sandtrace
{
    std::list<mesh>&& load_meshes(std::string fbx_filename);

    std::list<mesh>&& extract_mesh_list(FbxNode* node);
}

#endif
