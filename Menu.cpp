#include "Menu.hpp"

m1::Menu::Menu(
	std::unordered_map<std::string, Mesh*> menuObjects,
	gfxc::TextRenderer* textRenderer,
	glm::ivec2 resolution)
{
	this->menuObjects = menuObjects;
	this->textRenderer = textRenderer;
	this->resolution = resolution;
}

m1::Menu::~Menu()
{
}

void m1::Menu::RenderMenu(std::unordered_map<std::string, Shader*> shaders)
{
	// Render background
	glm::mat4 modelMatrix = glm::mat4(1);
	m1::InitTema2::RenderMesh(menuObjects["background"], shaders["ShaderTank"], modelMatrix);

	// Render button 1 (play)
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 7, 1));
	m1::InitTema2::RenderMesh(menuObjects["button"], shaders["ShaderTank"], modelMatrix);

	// Render button 2 (quit)
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(1, -1, 1));
	m1::InitTema2::RenderMesh(menuObjects["button"], shaders["ShaderTank"], modelMatrix);

	// Place "Start" text on button 1
	textRenderer->RenderText("Start", (float)(resolution.x / 2 - 100), (float)(resolution.y / 2 - 195), 2.5f, kTextColor);

	// Place "Start" text on button 1
	textRenderer->RenderText("Stop", (float)(resolution.x / 2 - 90), (float)(resolution.y / 2), 2.5f, kTextColor);
}

int m1::Menu::CheckButtonPress(float mouseX, float mouseY)
{
	// Return 1 if button 1 was pressed
	if (mouseX >= button1PositionStartX &&
		mouseX <= button1PositionEndX &&
		mouseY >= button1PositionStartY &&
		mouseY <= button1PositionEndY)
	{
		return 1;
	}

	// Return 2 if button 2 was pressed
	if (mouseX >= button2PositionStartX &&
		mouseX <= button2PositionEndX &&
		mouseY >= button2PositionStartY &&
		mouseY <= button2PositionEndY)
	{
		return 2;
	}

	// Return 0 if no button was pressed
	return 0;
}
