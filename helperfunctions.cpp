#include "helperfunctions.h"

namespace raintrace
{
	scene build_sphere_scene()
	{
		auto primitives = scene::primitive_vector{};
	}
	
	void save_scene(image_data img_data, string filename){
	  
	  
	  
	  boost::gil::planar_rgb_view view = boost::gil::planar_rgb_view(img_data.getWidth(), img_data.getHeight(), img_data.getR(), img_data.getG(), img_data.getB(), img_data.getWidth());
	  
	  boost::gil::jpeg_write_view("scene.jpg", view);
	  
	}
	
}
