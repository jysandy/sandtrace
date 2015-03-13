#ifndef __MESH_H__
#define __MESH_H__

#include <list>
#include <string>

#include "triangle.hpp"
#include "material.hpp"

namespace sandtrace
{
    class mesh
    {
    public:

        std::list<triangle> triangles;
        material mat;
    };
}

#endif
