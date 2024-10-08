#include "lighting/point_light.hpp"
#include "lighting/colour.hpp"
#include "serdes/json.hpp"

namespace sandtrace
{
	void from_json(const nlohmann::json& j, point_light& p)
	{
		glm::vec4 colour = convert_to_linear_space(vec_from_json<4>(j.at("colour")));
		p.ambient	 = j.at("ambient_factor").get<float>() * colour;
		p.diffuse	 = j.at("diffuse_factor").get<float>() * colour;
		p.specular	 = j.at("specular_factor").get<float>() * colour;
		p.position	 = vec_from_json<3>(j.at("position"));
		p.brightness = j.at("brightness");
		p.a1		 = j.at("a1");
		p.a2		 = j.at("a2");
	}
}