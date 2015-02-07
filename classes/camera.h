#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>

namespace raintrace
{
	class camera
	{
	public:
		camera(glm::vec4 look_from, glm::vec4 look_at, glm::vec4 up, float fov);
		
		const glm::vec4 look_from;
		const glm::vec4 look_at;
		const glm::vec4 up;
		const float fov;
	};
}

#endif