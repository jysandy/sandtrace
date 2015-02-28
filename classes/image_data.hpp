#ifndef __IMAGE_DATA_H__
#define __IMAGE_DATA_H__

#include <glm/glm.hpp>
#include <vector>

namespace sandtrace
{
	class image_data
	{
	public:
		image_data(int render_width, int render_height);

		glm::vec4& operator()(int x, int y);

		const int render_width;
		const int render_height;

	private:
		std::vector<std::vector<glm::vec4>> color_matrix;
	};
}

#endif
