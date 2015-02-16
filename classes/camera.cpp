#include "camera.h"

namespace sandtrace
{
	camera::camera(glm::vec3 look_from, glm::vec3 look_at, glm::vec3 up, float fov) :
	look_from(look_from), look_at(look_at), up(up), fov(fov)
	{
	}
}
