#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "components/simple_scene.h"
#include "components/text_renderer.h"
#include "lab_camera.hpp"
#include "Init.hpp"


namespace m1
{
	class Menu
	{
	public:
		Menu(
			std::unordered_map<std::string, Mesh*> menuObjects,
			gfxc::TextRenderer* textRenderer, 
			glm::ivec2 resolution);
		~Menu();
		void RenderMenu(std::unordered_map<std::string, Shader*> shaders);
		int CheckButtonPress(float mouseX, float mouseY);

	private:
		std::unordered_map<std::string, Mesh*> menuObjects;
		gfxc::TextRenderer* textRenderer;
		const glm::vec3 kTextColor = NormalizedRGB(0, 0, 0);
		const glm::vec3 kBackgroundColor = NormalizedRGB(41, 45, 62);
		glm::ivec2 resolution;
		float buttonWidth = 18.0f;
		float buttonHeight = 5.0f;

		float button1PositionStartX = 400;
		float button1PositionStartY = 120;
		float button1PositionEndX = 830;
		float button1PositionEndY = 240;

		float button2PositionStartX = 400;
		float button2PositionStartY = 320;
		float button2PositionEndX = 830;
		float button2PositionEndY = 440;

		glm::vec3 button2Position = glm::vec3(1, -1, 1);
	};
}