#ifndef __MESH_H__
#define __MESH_H__

#include <string>
#include <list>
#include <utility>

#include "triangle.hpp"
#include "material.hpp"

namespace sandtrace
{
    class mesh
    {
    public:

        std::list<std::shared_ptr<triangle>> triangles;
        material mat;
    };
}

#endif
