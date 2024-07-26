#include "serdes/json.hpp"
#include "textures/texture.hpp"
#include "textures/monochrome_texture.hpp"

namespace sandtrace
{
	void from_json(const nlohmann::json& j, std::shared_ptr<texture>& t)
	{
		std::string texture_type = j.at("type");
		if (texture_type == "monochrome")
		{
			t = std::make_shared<monochrome_texture>(vec_from_json<4>(j.at("colour")));
		}
		else
		{
			throw std::runtime_error("Can't read texture of type: " + texture_type);
		}
	}
}