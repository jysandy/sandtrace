#include "texture_pool.hpp"

namespace sandtrace
{
    std::shared_ptr<texture> texture_pool::get(std::string texname)
    {
        auto it = this->tex_map.find(texname);

        if (it == this->tex_map.end())
        {
            auto ret = std::make_shared<texture>(texname);
            this->tex_map.insert(std::make_pair(texname, ret));
            return ret;
        }

        return it->second;
    }
}
