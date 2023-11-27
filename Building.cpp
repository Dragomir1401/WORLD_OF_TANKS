#include "Building.hpp"

m1::Building::Building(std::unordered_map<std::string, Mesh*> buildingObjects)
{
	this->buildingObjects = buildingObjects;
}

m1::Building::~Building()
{
}

void m1::Building::RenderBuilding(std::unordered_map<std::string, Shader*> shaders)
{
	for (int i = 0; i < 1; ++i) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, buildingBaseHeight, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -i * buildingLength));
		m1::InitTema2::RenderMesh(buildingObjects["cottage1"], shaders["ShaderTank"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, buildingBaseHeight, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-4 * buildingLength, 0, 0));
		m1::InitTema2::RenderMesh(buildingObjects["cottage4"], shaders["ShaderTank"], modelMatrix);
	}

	for (int i = 1; i < 2; ++i) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, buildingBaseHeight, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -i * buildingLength));
		m1::InitTema2::RenderMesh(buildingObjects["cottage2"], shaders["ShaderTank"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, buildingBaseHeight, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-i * buildingLength, 0, 0));
		m1::InitTema2::RenderMesh(buildingObjects["cottage5"], shaders["ShaderTank"], modelMatrix);
	}

	for (int i = 2; i < 3; ++i) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, buildingBaseHeight, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -i * buildingLength));
		m1::InitTema2::RenderMesh(buildingObjects["cottage3"], shaders["ShaderTank"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, buildingBaseHeight, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-i * buildingLength, 0, 0));
		m1::InitTema2::RenderMesh(buildingObjects["tower"], shaders["ShaderTank"], modelMatrix);
	}

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, buildingBaseHeight, 0));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-2 * buildingLength, 0, -2 * buildingLength));
	m1::InitTema2::RenderMesh(buildingObjects["church"], shaders["ShaderTank"], modelMatrix);
}
