#include "Explosion.hpp"

m1::Explosion::Explosion(
	std::unordered_map<std::string, Mesh*> meshes, 
	glm::vec3 position)

{
	this->meshes = meshes;
	this->position = position;
}

m1::Explosion::~Explosion()
{
}

bool m1::Explosion::RendExplosion(std::unordered_map<std::string, Shader*> shaders)
{
	this->animationIndex++;

	if (this->animationIndex > 25)
	{
		return false;
	}

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, this->position);

	m1::InitTema2::RenderMesh(
		this->meshes["explosion" + std::to_string(this->animationIndex)],
		shaders["ShaderTank"],
		modelMatrix);

	return true;
}

int m1::Explosion::GetAnimationIndex()
{
	return this->animationIndex;
}




