#include <string>
#include <iostream>
#include "components/simple_scene.h"
#include "lab_camera.hpp"
#include "Init.hpp"


namespace m1
{
	class Button
	{
	public:
		Button(
			std::string text,
			glm::vec2 position,
			glm::vec2 size);
		~Button();

	private:
		std::string text;
		glm::vec2 position;
		glm::vec2 size;
	};
} // namespace m1