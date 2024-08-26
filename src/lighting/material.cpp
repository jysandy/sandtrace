#include "lighting/material.hpp"
#include "lighting/colour.hpp"
#include "serdes/json.hpp"

namespace sandtrace
{
	void from_json(const nlohmann::json& j, material& m)
	{
		m.ambient	  = convert_to_linear_space(vec_from_json<4>(j.at("ambient")));
		m.diffuse	  = convert_to_linear_space(vec_from_json<4>(j.at("diffuse")));
		m.specular	  = convert_to_linear_space(vec_from_json<4>(j.at("specular")));
		m.shininess	  = j.at("shininess");
		m.reflectance = j.at("reflectance");
	}
}