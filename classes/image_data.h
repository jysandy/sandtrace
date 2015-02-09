#ifndef __IMAGE_DATA_H__
#define __IMAGE_DATA_H__

namespace raintrace
{
	class image_data
	{
	public:
		image_data(
			int render_width,
			int render_height);
		
		int render_width;
		int render_height;
	};
}

#endif 
