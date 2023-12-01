#include "Button.hpp"

m1::Button::Button(
	std::string text,
	glm::vec2 position,
	glm::vec2 size)
{
	this->text = text;
	this->position = position;
	this->size = size;
}

m1::Button::~Button()
{
}
