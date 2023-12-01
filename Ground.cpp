#include "Ground.hpp"

m1::Ground::Ground(std::unordered_map<std::string, Mesh*> groundObjects)
{
	this->groundObjects = groundObjects;
}

m1::Ground::~Ground()
{
}

void m1::Ground::RenderGround(std::unordered_map<std::string, Shader*> shaders, bool minimap)
{
    glm::mat4 modelMatrix;
    std::vector<glm::vec3> translations;

    for (int i = -groundBoxNumbers; i <= groundBoxNumbers; ++i) {
        for (int j = -groundBoxNumbers; j <= groundBoxNumbers; ++j) {
            translations.push_back(glm::vec3(i * groundLength, groundHeight, j * groundLength));
        }
    }

    for (const glm::vec3& translation : translations) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, translation);

        if (!minimap)
        {
            m1::InitTema2::RenderMesh(groundObjects["ground"], shaders["ShaderTank"], modelMatrix);
        }
        else
        {
            m1::InitTema2::RenderMeshMinimap(groundObjects["ground"], shaders["ShaderTank"], modelMatrix);
        }
    }
}
