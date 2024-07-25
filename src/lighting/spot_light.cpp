#include <glm/glm.hpp>

#include "lighting/spot_light.hpp"
#include "lighting/colour.hpp"
#include "serdes/json.hpp"

namespace sandtrace
{
	void from_json(const nlohmann::json& j, spot_light& s)
	{
		glm::vec4 colour = vec_from_json<4>(j.at("colour"));
		s.ambient	 = saturate(j.at("ambient_factor").template get<float>() * colour);
		s.diffuse	 = saturate(j.at("diffuse_factor").template get<float>() * colour);
		s.specular	 = saturate(j.at("specular_factor").template get<float>() * colour);
		s.position	 = vec_from_json<3>(j.at("position"));
		glm::vec3 look_at = vec_from_json<3>(j.at("look_at"));
		s.direction	 = glm::normalize(look_at - s.position);
		s.brightness = j.at("brightness");
		s.a1		 = j.at("a1");
		s.a2		 = j.at("a2");
		s.angle		 = glm::radians(j.at("angle_degrees") / 2.0f);
		s.power		 = j.at("power");
	}
}