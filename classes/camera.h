#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>

namespace raintrace
{
	class camera
	{
	public:
		camera(glm::vec4 look_from, glm::vec4 look_at, glm::vec4 up, float fov);
		
		glm::vec4 look_from;
		glm::vec4 look_at;
		glm::vec4 up;
		float fov;
	};
}

#endif