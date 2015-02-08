#include "scene.h"

namespace raintrace
{
	scene::scene(camera c, scene::primitive_vector p,
		std::vector<directional_light> directional_lights,
		std::vector<point_light> point_lights,
		std::vector<spot_light> spot_lights) : 
		cam(c), primitives(p),
		directional_lights(directional_lights),
		point_lights(point_lights),
		spot_lights(spot_lights)
	{
	}
}
	
