#ifndef __MESH_H__
#define __MESH_H__

#include <string>
#include <list>
#include <utility>
#include <memory>

#include "triangle.hpp"
#include "material.hpp"

namespace sandtrace
{
    struct mesh
    {
        std::list<std::shared_ptr<triangle>> triangles;
        material mat;
        std::shared_ptr<texture> tex;
    };
}

#endif
