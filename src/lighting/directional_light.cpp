#include "lighting/directional_light.hpp"
#include "lighting/colour.hpp"

namespace sandtrace
{
	void from_json(const nlohmann::json& j, directional_light& d)
	{
		d.ambient = convert_to_linear_space(vec_from_json<4>(j["ambient"]));
		d.diffuse = convert_to_linear_space(vec_from_json<4>(j["diffuse"]));
		d.specular = convert_to_linear_space(vec_from_json<4>(j["specular"]));
		d.direction = glm::normalize(vec_from_json<3>(j["direction"]));
	}
}

