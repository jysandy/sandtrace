#ifndef __TEXTURE_POOL_H__
#define __TEXTURE_POOL_H__

#include <map>
#include <string>
#include <memory>

#include "texture.hpp"
#include "image_texture.hpp"

namespace sandtrace
{
    class texture_pool
    {
    public:
        std::shared_ptr<texture> get(std::string texname);

    private:
        std::map<std::string, std::shared_ptr<texture>> tex_map;
    };
}

#endif
