#include "Sky.hpp"

m1::Sky::Sky(std::unordered_map<std::string, Mesh*> skyObjects)
{
	this->skyObjects = skyObjects;
}

m1::Sky::~Sky()
{
}

void m1::Sky::RenderSky(std::unordered_map<std::string, Shader*> shaders)
{
	glm::mat4 modelMatrix;
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(skyScale));
	m1::InitTema2::RenderMesh(skyObjects["sky"], shaders["ShaderTank"], modelMatrix);
}
