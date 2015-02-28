#include "image_data.hpp"

namespace sandtrace{
	image_data::image_data(
		int render_width,
		int render_height)
		: render_width(render_width), render_height(render_height)
	{
		for (int i = 0; i < render_width; i++)
		{
			this->color_matrix.push_back(std::vector<glm::vec4>(render_height));
		}
	}

	glm::vec4& image_data::operator()(int x, int y)
	{
		return color_matrix[x][y];
	}
}
