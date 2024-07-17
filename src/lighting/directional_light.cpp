#include "lighting/directional_light.hpp"

namespace sandtrace
{
	void from_json(const nlohmann::json& j, directional_light& d)
	{
		d.ambient = vec_from_json<4>(j["ambient"]);
		d.diffuse = vec_from_json<4>(j["diffuse"]);
		d.specular = vec_from_json<4>(j["specular"]);
		d.direction = glm::normalize(vec_from_json<3>(j["direction"]));
	}
}

