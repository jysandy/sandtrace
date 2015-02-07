#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <glm/glm.hpp>

namespace raintrace
{
	class material
	{
	public:
		material(glm::vec4 diffuse,
				 glm::vec4 ambient,
				 glm::vec4 specular,
				 float shininess,
				 float reflectance
				);
		
		const glm::vec4 diffuse;
		const glm::vec4 ambient;
		const glm::vec4 specular;
		const float shininess;
		const float reflectance;
	};
}

#endif