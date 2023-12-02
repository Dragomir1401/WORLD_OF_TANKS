#include "StatsText.hpp"

m1::StatsText::StatsText(gfxc::TextRenderer* textRenderer, glm::ivec2 resolution)
{
	this->textRenderer = textRenderer;
	this->resolution = resolution;
}

m1::StatsText::~StatsText()
{
}

void m1::StatsText::RenderStatsText(std::unordered_map<std::string, Shader*> shaders, int kills, int landedShots)
{
	// Render kills in the left upper corner
	textRenderer->RenderText("Kills: " + std::to_string(kills), 10.0f, 30.0f, 1.0f, kTextColor);

	// Render landed shots in left upper corner under kills
	textRenderer->RenderText("Landed shots: " + std::to_string(landedShots), 10.0f, 60.0f, 1.0f, kTextColor);
}

