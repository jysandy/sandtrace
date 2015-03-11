#ifndef __MESH_H__
#define __MESH_H__

#include <vector>
#include <string>

#include "triangle.hpp"
#include "material.hpp"

namespace sandtrace
{
    class mesh
    {
    public:

        static mesh from_fbx_file(std::string filename);

        std::vector<triangle> triangles;
        material mat;
    };
}

#endif
