#ifndef __SANDTRACE_SERDES_JSON_HPP__
#define __SANDTRACE_SERDES_JSON_HPP__

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

#include "textures/texture.hpp"

namespace sandtrace
{
    template <size_t _Size>
    glm::vec<_Size, float, glm::packed_highp> vec_from_json(const nlohmann::json& j)
    {
        auto vec = glm::vec<_Size, float, glm::packed_highp>();
        std::array<float, _Size> parsed = j.template get<std::array<float, _Size>>();
        for (auto i = 0; i < _Size; i++)
        {
            vec[i] = parsed[i];
        }

        return vec;
    }

    void from_json(const nlohmann::json& j, std::shared_ptr<texture>& t);
}

#endif // !__SANDTRACE_SERDES_JSON_HPP__
