#include "lighting/spot_light.hpp"
#include "lighting/colour.hpp"
#include "serdes/json.hpp"

namespace sandtrace
{
	void from_json(const nlohmann::json& j, spot_light& s)
	{
		glm::vec4 colour = vec_from_json<4>(j["colour"]);
		s.ambient = saturate(j["ambient_factor"].template get<float>() * colour);
		s.diffuse = saturate(j["diffuse_factor"].template get<float>() * colour);
		s.specular = saturate(j["specular_factor"].template get<float>() * colour);
		s.position = vec_from_json<3>(j["position"]);
		glm::vec3 look_at = vec_from_json<3>(j["look_at"]);
		s.direction = glm::normalize(look_at - s.position);
		s.a0 = j["a0"].template get<float>();
		s.a1 = j["a1"].template get<float>();
		s.a2 = j["a2"].template get<float>();
		s.power = j["power"].template get<float>();
	}
}