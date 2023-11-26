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
    glm::mat4 modelMatrix;
    std::vector<glm::vec3> translations;

    for (int i = -1; i <= 2; ++i) {
        for (int j = -1; j <= 2; ++j) {
            translations.push_back(glm::vec3(i * groundLength, groundHeight, j * groundLength));
        }
    }

    for (const glm::vec3& translation : translations) {
        modelMatrix = glm::mat4(1); // Reset the model matrix to the identity matrix.
        modelMatrix = glm::translate(modelMatrix, translation); // Apply the translation.
        m1::InitTema2::RenderMesh(groundObjects["ground"], shaders["ShaderTank"], modelMatrix);
    }
}
