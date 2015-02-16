#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>

namespace sandtrace
{
	class camera
	{
	public:
		camera(glm::vec3 look_from, glm::vec3 look_at, glm::vec3 up, float fov);

		glm::vec3 look_from;
		glm::vec3 look_at;
		glm::vec3 up;
		float fov;
	};
}

#endif
