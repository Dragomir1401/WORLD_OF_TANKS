#include "ShadersAndRenders.hpp"


m1::ShadersAndRenders::ShadersAndRenders(
    std::unordered_map<std::string, 
    Shader*> shaders, Camera* camera,
    glm::mat4 projectionMatrix)
{
	this->shaders = shaders;
    this->camera = camera;
    this->projectionMatrix = projectionMatrix;
}

m1::ShadersAndRenders::~ShadersAndRenders()
{
}

void m1::ShadersAndRenders::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}
