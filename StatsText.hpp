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
	class StatsText
	{
	public:
		StatsText(
			gfxc::TextRenderer* textRenderer,
			glm::ivec2 resolution);
		~StatsText();

		void RenderStatsText(
			std::unordered_map<std::string,
			Shader*> shaders,
			int kills,
			int landedShots);
		void RenderDeathText(
			std::unordered_map<std::string, Shader*> shaders);

	private:
		gfxc::TextRenderer* textRenderer;
		const glm::vec3 kTextColor = NormalizedRGB(0, 0, 0);
		const glm::vec3 kBackgroundColor = NormalizedRGB(41, 45, 62);
		glm::ivec2 resolution;
	};
}