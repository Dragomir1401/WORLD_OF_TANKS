#include "Ground.hpp"

m1::Ground::Ground(std::unordered_map<std::string, Mesh*> groundObjects)
{
	this->groundObjects = groundObjects;
}

m1::Ground::~Ground()
{
}

void m1::Ground::RenderGround(std::unordered_map<std::string, Shader*> shaders)
{
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0, groundHeight, 0));
    m1::InitTema2::RenderMesh(groundObjects["ground"], shaders["ShaderTank"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(groundLength, groundHeight, 0));
    m1::InitTema2::RenderMesh(groundObjects["ground"], shaders["ShaderTank"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-groundLength, groundHeight, 0));
    m1::InitTema2::RenderMesh(groundObjects["ground"], shaders["ShaderTank"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0, groundHeight, -groundLength));
    m1::InitTema2::RenderMesh(groundObjects["ground"], shaders["ShaderTank"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0, groundHeight, groundLength));
    m1::InitTema2::RenderMesh(groundObjects["ground"], shaders["ShaderTank"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(groundLength, groundHeight, groundLength));
    m1::InitTema2::RenderMesh(groundObjects["ground"], shaders["ShaderTank"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-groundLength, groundHeight, -groundLength));
    m1::InitTema2::RenderMesh(groundObjects["ground"], shaders["ShaderTank"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-groundLength, groundHeight, groundLength));
    m1::InitTema2::RenderMesh(groundObjects["ground"], shaders["ShaderTank"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(groundLength, groundHeight, -groundLength));
    m1::InitTema2::RenderMesh(groundObjects["ground"], shaders["ShaderTank"], modelMatrix);
}
