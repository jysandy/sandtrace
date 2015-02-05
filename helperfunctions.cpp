#include "helperfunctions.h"

namespace raintrace
{
	Scene buildSphereScene()
	{
		auto primitives = Scene::PrimitiveVector{};
	}
	
	void save_scene(ImageData img_data, string filename){
	  
	  
	  
	  boost::gil::planar_rgb_view view = boost::gil::planar_rgb_view(img_data.getWidth(), img_data.getHeight(), img_data.getR(), img_data.getG(), img_data.getB(), img_data.getWidth());
	  
	  boost::gil::jpeg_write_view("scene.jpg", view);
	  
	}
	
}
