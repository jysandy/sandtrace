#include "camera.h"

namespace sandtrace
{
	camera::camera(glm::vec4 look_from, glm::vec4 look_at, glm::vec4 up, float fov) :
	look_from(look_from), look_at(look_at), up(up), fov(fov)
	{
	}
}