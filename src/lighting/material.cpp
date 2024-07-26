#include "lighting/material.hpp"
#include "serdes/json.hpp"

namespace sandtrace
{
	void from_json(const nlohmann::json& j, material& m)
	{
		m.ambient	  = vec_from_json<4>(j.at("ambient"));
		m.diffuse	  = vec_from_json<4>(j.at("diffuse"));
		m.specular	  = vec_from_json<4>(j.at("specular"));
		m.shininess	  = j.at("shininess");
		m.reflectance = j.at("reflectance");
	}
}