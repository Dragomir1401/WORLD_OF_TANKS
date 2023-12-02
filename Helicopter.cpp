#include "Helicopter.hpp"

m1::Helicopter::Helicopter(std::unordered_map<std::string, Mesh*> tankObjects, glm::vec3 initialPosition)
{
	this->helicopterObjects = tankObjects;
	this->initialPosition = initialPosition;
}

m1::Helicopter::~Helicopter()
{
}

glm::mat4 m1::Helicopter::RenderBody(
    std::unordered_map<std::string, Shader*> shaders,
    glm::vec3 helicopterTranslate,
    glm::vec3 helicopterRotate,
    bool minimap)
{
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, initialPosition);
    modelMatrix = glm::translate(modelMatrix, helicopterTranslate);
    modelMatrix = glm::rotate(modelMatrix, helicopterRotate.y, glm::vec3(0, 1, 0));

    if (!minimap)
    {
        m1::InitTema2::RenderMesh(helicopterObjects["body"], shaders["ShaderTank"], modelMatrix, damage);
    }
    else
    {
        m1::InitTema2::RenderMeshMinimap(helicopterObjects["body"], shaders["ShaderTank"], modelMatrix, damage);
    }


    return modelMatrix;
}

void m1::Helicopter::RenderBlade(
    std::unordered_map<std::string, Shader*> shaders,
    glm::vec3 helicopterTranslate,
    glm::vec3 helicopterRotate,
    int animationIndex,
    bool minimap)
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, initialPosition);
	modelMatrix = glm::translate(modelMatrix, helicopterTranslate);
	modelMatrix = glm::rotate(modelMatrix, helicopterRotate.y, glm::vec3(0, 1, 0));

    std::string name = "blade" + std::to_string(animationIndex);
    if (!minimap)
    {
        m1::InitTema2::RenderMesh(helicopterObjects[name], shaders["ShaderTank"], modelMatrix, damage);
	}
    else
    {
		m1::InitTema2::RenderMeshMinimap(helicopterObjects[name], shaders["ShaderTank"], modelMatrix, damage);
	}
}

void m1::Helicopter::RenderBackBlade(
    std::unordered_map<std::string, Shader*> shaders, 
    glm::vec3 helicopterTranslate,
    glm::vec3 helicopterRotate, 
    int animationIndex,
    bool minimap)
{
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, initialPosition);
    modelMatrix = glm::translate(modelMatrix, helicopterTranslate);
    modelMatrix = glm::rotate(modelMatrix, helicopterRotate.y, glm::vec3(0, 1, 0));

    std::string name = "backBlade" + std::to_string(animationIndex);
    if (!minimap)
    {
        m1::InitTema2::RenderMesh(helicopterObjects[name], shaders["ShaderTank"], modelMatrix, damage);
    }
    else
    {
        m1::InitTema2::RenderMeshMinimap(helicopterObjects[name], shaders["ShaderTank"], modelMatrix, damage);
    }
}
