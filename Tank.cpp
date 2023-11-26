#include "Tank.hpp"

m1::Tank::Tank(std::unordered_map<std::string, Mesh*> tankObjects)
{
    this->tankObjects = tankObjects;
}

m1::Tank::~Tank()
{
}

glm::mat4 m1::Tank::RenderBody(
    std::unordered_map<std::string, Shader*> shaders,
    glm::vec3 tankTranslate,
    glm::vec3 tankRotate)
{
    glm::vec3 tankAdjustedTranslate = tankTranslate / tankScale;

    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(tankScale));
    modelMatrix = glm::translate(modelMatrix, tankAdjustedTranslate);
    modelMatrix = glm::rotate(modelMatrix, tankRotate.y, glm::vec3(0, 1, 0));
    m1::InitTema2::RenderMesh(tankObjects["body"], shaders["ShaderTank"], modelMatrix);

    return modelMatrix;
}


m1::TurretOrientation m1::Tank::RenderTurret(
    std::unordered_map<std::string, Shader*> shaders,
    glm::vec3 tankTranslate,
    glm::vec3 tankRotate,
    glm::vec3 mouseRotate)
{
    glm::vec3 tankAdjustedTranslate = tankTranslate / tankScale;
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(tankScale));
    modelMatrix = glm::translate(modelMatrix, tankAdjustedTranslate);
    modelMatrix = glm::rotate(modelMatrix, tankRotate.y, glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, -mouseRotate.y, glm::vec3(0, 1, 0));
    m1::InitTema2::RenderMesh(tankObjects["turet"], shaders["ShaderTank"], modelMatrix);

    TurretOrientation turretOrientation;
    turretOrientation.turretRelativeRotationWhenBulletWasShot = tankRotate + glm::vec3(0, -mouseRotate.y, 0);
    turretOrientation.turretWorldMatrixWhenBulletWasShot = modelMatrix;

    return turretOrientation;
}

void m1::Tank::RenderTun(
    std::unordered_map<std::string,
    Shader*> shaders,
    glm::vec3 tankTranslate,
    glm::vec3 tankRotate, 
    glm::vec3 mouseRotate)
{
    glm::vec3 tankAdjustedTranslate = tankTranslate / tankScale;
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(tankScale));
    modelMatrix = glm::translate(modelMatrix, tankAdjustedTranslate);
    modelMatrix = glm::rotate(modelMatrix, tankRotate.y, glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, -mouseRotate.y, glm::vec3(0, 1, 0));
    m1::InitTema2::RenderMesh(tankObjects["tun"], shaders["ShaderTank"], modelMatrix);
}


void m1::Tank::RenderWheels(
    std::unordered_map<std::string, Shader*> shaders, 
    glm::vec3 tankTranslate, 
    glm::vec3 tankRotate, 
    glm::vec3 wheelTilt, 
    int animationIndex)
{
    glm::vec3 wheelAdjustedTranslate = tankTranslate / wheelScale;
    glm::vec3 wheelAdjustedRotate = tankRotate;
    int animationIndexReverse = 250 - animationIndex + 1;

    {
        // Rend the wheel 1 out of 8 at animationIndex
        std::string name = "wheel" + std::to_string(animationIndexReverse);
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(wheelScale));
        modelMatrix = glm::translate(modelMatrix, wheelAdjustedTranslate);
        modelMatrix = glm::rotate(modelMatrix, tankRotate.y, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(3.4f, -0.39f, 0.35f));
        modelMatrix = glm::rotate(modelMatrix, wheelTilt.y, glm::vec3(0, 1, 0));
        m1::InitTema2::RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
    }

    {
        // Rend the wheel 2 out of 8 at animationIndex
        std::string name = "wheel" + std::to_string(animationIndexReverse);
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(wheelScale));
        modelMatrix = glm::translate(modelMatrix, wheelAdjustedTranslate);
        modelMatrix = glm::rotate(modelMatrix, tankRotate.y, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.9f, -0.42f, 0.35f));
        m1::InitTema2::RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
    }

    {
        // Rend the wheel 3  out of 8 at animationIndex
        std::string name = "wheel" + std::to_string(animationIndexReverse);
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(wheelScale));
        modelMatrix = glm::translate(modelMatrix, wheelAdjustedTranslate);
        modelMatrix = glm::rotate(modelMatrix, tankRotate.y, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.6f, -0.42f, 0.35f));
        m1::InitTema2::RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
    }

    {
        // Rend the wheel 4 out of 8 at animationIndex
        std::string name = "wheel" + std::to_string(animationIndexReverse);
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(wheelScale));
        modelMatrix = glm::translate(modelMatrix, wheelAdjustedTranslate);
        modelMatrix = glm::rotate(modelMatrix, tankRotate.y, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.7f, -0.42f, 0.35f));
        m1::InitTema2::RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
    }

    {
        // Rend the wheel 5 out of 8 at animationIndex
        std::string name = "wheel" + std::to_string(animationIndex);
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(wheelScale));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(180), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, -wheelAdjustedTranslate);
        modelMatrix = glm::rotate(modelMatrix, tankRotate.y, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(3.8f, -0.39f, 0.35f));
        m1::InitTema2::RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
    }

    {
        // Rend the wheel 6 out of 8 at animationIndex
        std::string name = "wheel" + std::to_string(animationIndex);
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(wheelScale));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(180), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, -wheelAdjustedTranslate);
        modelMatrix = glm::rotate(modelMatrix, tankRotate.y, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1.7f, -0.42f, 0.35f));
        m1::InitTema2::RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
    }

    {
        // Rend the wheel 7 out of 8 at animationIndex
        std::string name = "wheel" + std::to_string(animationIndex);
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(wheelScale));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(180), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, -wheelAdjustedTranslate);
        modelMatrix = glm::rotate(modelMatrix, tankRotate.y, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.8f, -0.42f, 0.35f));
        m1::InitTema2::RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
    }

    {
        // Rend the wheel 8 out of 8 at animationIndex
        std::string name = "wheel" + std::to_string(animationIndex);
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(wheelScale));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(180), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, -wheelAdjustedTranslate);
        modelMatrix = glm::rotate(modelMatrix, tankRotate.y, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.4f, -0.42f, 0.35f));
        modelMatrix = glm::rotate(modelMatrix, wheelTilt.y, glm::vec3(0, 1, 0));
        m1::InitTema2::RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
    }
}

