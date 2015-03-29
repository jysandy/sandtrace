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
    class mesh
    {
    public:
        mesh(std::list<std::shared_ptr<triangle>> t, material m, std::shared_ptr<texture> tx) :
        triangles(t), mat(m), tex(tx)
        {
        }

        std::list<std::shared_ptr<triangle>> triangles;
        material mat;
        std::shared_ptr<texture> tex;
    };
}

#endif
