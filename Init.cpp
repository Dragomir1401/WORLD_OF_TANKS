﻿#include "lab_m1/tema2/Init.hpp"

#include <vector>
#include <string>
#include <iostream>
#include "init.hpp"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


InitTema2::InitTema2()
{
}


InitTema2::~InitTema2()
{
}

void InitTema2::CreateTankEntity()
{
    const string sourceObjDir = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects");
    const string sourceObjDirTank = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "tank", "terog");
    {
        Mesh* mesh = new Mesh("body");
        mesh->LoadMesh(sourceObjDirTank, "body.obj");
        tankObjects["body"] = mesh;
    }

    {
		Mesh* mesh = new Mesh("tun");
		mesh->LoadMesh(sourceObjDirTank, "tunGun.obj");
		tankObjects["tun"] = mesh;
	}

    {
        Mesh* mesh = new Mesh("turet");
        mesh->LoadMesh(sourceObjDirTank, "tun.obj");
        tankObjects["turet"] = mesh;
    }

    // for to 250 load wheel
    for (int i = 1; i <= 250; i++)
    {
		string name = "wheel" + to_string(i);
		string nameObj = "wheel" + to_string(i) + ".obj";
		Mesh* mesh = new Mesh(name);
		mesh->LoadMesh(sourceObjDirTank, nameObj);
		tankObjects[name] = mesh;
	}
}

void InitTema2::ParseTextures()
{
}

void m1::InitTema2::RenderTankEntity()
{
    float tankScale = 0.35f;
    float wheelScale = 0.385f;
    glm::vec3 tankAdjustedTranslate = tankTranslate / tankScale;
    glm::vec3 wheelAdjustedTranslate = tankTranslate / wheelScale;
    glm::vec3 tankAdjustedRotate = tankRotate;
    glm::vec3 wheelAdjustedRotate = tankRotate;
    glm::vec3 wheelAdjustedTilt = wheelTilt;
    int animationIndexReverse = 250 - animationIndex + 1;

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(tankScale));
        modelMatrix = glm::translate(modelMatrix, tankAdjustedTranslate);
        modelMatrix = glm::rotate(modelMatrix, tankAdjustedRotate.y, glm::vec3(0, 1, 0));
        RenderMesh(tankObjects["body"], shaders["ShaderTank"], modelMatrix);
    }

   {
       glm::vec3 mouseRotation = ComputeRotationBasedOnMouse();
       glm::mat4 modelMatrix = glm::mat4(1);
       modelMatrix = glm::scale(modelMatrix, glm::vec3(tankScale));
       modelMatrix = glm::translate(modelMatrix, tankAdjustedTranslate);
       modelMatrix = glm::rotate(modelMatrix, tankAdjustedRotate.y, glm::vec3(0, 1, 0));
       modelMatrix = glm::rotate(modelMatrix, -mouseRotation.y, glm::vec3(0, 1, 0));
       RenderMesh(tankObjects["turet"], shaders["ShaderTank"], modelMatrix);
   }

   {
        glm::vec3 mouseRotation = ComputeRotationBasedOnMouse();
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(tankScale));
        modelMatrix = glm::translate(modelMatrix, tankAdjustedTranslate);
        modelMatrix = glm::rotate(modelMatrix, tankAdjustedRotate.y, glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, -mouseRotation.y, glm::vec3(0, 1, 0));
        RenderMesh(tankObjects["tun"], shaders["ShaderTank"], modelMatrix);
   }
   
   {
       // Rend the wheel 1 out of 8 at animationIndex
       string name = "wheel" + to_string(animationIndexReverse);
       glm::mat4 modelMatrix = glm::mat4(1);
       modelMatrix = glm::scale(modelMatrix, glm::vec3(wheelScale));
       modelMatrix = glm::translate(modelMatrix, wheelAdjustedTranslate);
       modelMatrix = glm::rotate(modelMatrix, wheelAdjustedRotate.y, glm::vec3(0, 1, 0));
       modelMatrix = glm::translate(modelMatrix, glm::vec3(3.4f, -0.39f, 0.35f));
       modelMatrix = glm::rotate(modelMatrix, wheelAdjustedTilt.y, glm::vec3(0, 1, 0));
       RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
   }

   {
       // Rend the wheel 2 out of 8 at animationIndex
       string name = "wheel" + to_string(animationIndexReverse);
       glm::mat4 modelMatrix = glm::mat4(1);
       modelMatrix = glm::scale(modelMatrix, glm::vec3(wheelScale));
       modelMatrix = glm::translate(modelMatrix, wheelAdjustedTranslate);
       modelMatrix = glm::rotate(modelMatrix, wheelAdjustedRotate.y, glm::vec3(0, 1, 0));
       modelMatrix = glm::translate(modelMatrix, glm::vec3(0.9f, -0.42f, 0.35f));
       RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
   }

   {
       // Rend the wheel 3  out of 8 at animationIndex
       string name = "wheel" + to_string(animationIndexReverse);
       glm::mat4 modelMatrix = glm::mat4(1);
       modelMatrix = glm::scale(modelMatrix, glm::vec3(wheelScale));
       modelMatrix = glm::translate(modelMatrix, wheelAdjustedTranslate);
       modelMatrix = glm::rotate(modelMatrix, wheelAdjustedRotate.y, glm::vec3(0, 1, 0));
       modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.6f, -0.42f, 0.35f));
       RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
   }

   {
       // Rend the wheel 4 out of 8 at animationIndex
       string name = "wheel" + to_string(animationIndexReverse);
       glm::mat4 modelMatrix = glm::mat4(1);
       modelMatrix = glm::scale(modelMatrix, glm::vec3(wheelScale));
       modelMatrix = glm::translate(modelMatrix, wheelAdjustedTranslate);
       modelMatrix = glm::rotate(modelMatrix, wheelAdjustedRotate.y, glm::vec3(0, 1, 0));
       modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.7f, -0.42f, 0.35f));
       RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
   }

   {
       // Rend the wheel 5 out of 8 at animationIndex
       string name = "wheel" + to_string(animationIndex);
       glm::mat4 modelMatrix = glm::mat4(1);
       modelMatrix = glm::scale(modelMatrix, glm::vec3(wheelScale));
       modelMatrix = glm::rotate(modelMatrix, RADIANS(180), glm::vec3(0, 1, 0));
       modelMatrix = glm::translate(modelMatrix, -wheelAdjustedTranslate);
       modelMatrix = glm::rotate(modelMatrix, wheelAdjustedRotate.y, glm::vec3(0, 1, 0));
       modelMatrix = glm::translate(modelMatrix, glm::vec3(3.8f, -0.39f, 0.35f));
       RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
   }

   {
       // Rend the wheel 6 out of 8 at animationIndex
       string name = "wheel" + to_string(animationIndex);
       glm::mat4 modelMatrix = glm::mat4(1);
       modelMatrix = glm::scale(modelMatrix, glm::vec3(wheelScale));
       modelMatrix = glm::rotate(modelMatrix, RADIANS(180), glm::vec3(0, 1, 0));
       modelMatrix = glm::translate(modelMatrix, -wheelAdjustedTranslate);
       modelMatrix = glm::rotate(modelMatrix, wheelAdjustedRotate.y, glm::vec3(0, 1, 0));
       modelMatrix = glm::translate(modelMatrix, glm::vec3(1.7f, -0.42f, 0.35f));
       RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
   }

   {
       // Rend the wheel 7 out of 8 at animationIndex
       string name = "wheel" + to_string(animationIndex);
       glm::mat4 modelMatrix = glm::mat4(1);
       modelMatrix = glm::scale(modelMatrix, glm::vec3(wheelScale));
       modelMatrix = glm::rotate(modelMatrix, RADIANS(180), glm::vec3(0, 1, 0));
       modelMatrix = glm::translate(modelMatrix, -wheelAdjustedTranslate);
       modelMatrix = glm::rotate(modelMatrix, wheelAdjustedRotate.y, glm::vec3(0, 1, 0));
       modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.8f, -0.42f, 0.35f));
       RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
   }

   {
	   // Rend the wheel 8 out of 8 at animationIndex
	   string name = "wheel" + to_string(animationIndex);
	   glm::mat4 modelMatrix = glm::mat4(1);
	   modelMatrix = glm::scale(modelMatrix, glm::vec3(wheelScale));
       modelMatrix = glm::rotate(modelMatrix, RADIANS(180), glm::vec3(0, 1, 0));
       modelMatrix = glm::translate(modelMatrix, -wheelAdjustedTranslate);
       modelMatrix = glm::rotate(modelMatrix, wheelAdjustedRotate.y, glm::vec3(0, 1, 0));
	   modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.4f, -0.42f, 0.35f));
       modelMatrix = glm::rotate(modelMatrix, wheelAdjustedTilt.y, glm::vec3(0, 1, 0));
       RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
   }
}

void m1::InitTema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
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

void InitTema2::Init()
{
    CreateTankEntity();
    ParseTextures();

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader *shader = new Shader("ShaderTank");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "TextureVertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragTextureShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    camera = new Camera();
    camera->Set(glm::vec3(-5, 2.5f, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    initialCameraPosition = glm::vec3(-5, 2.5f, 0);
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    fov = 80.0f;
}

void InitTema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void InitTema2::UpdateAnimationTrackers(bool &animationIncreaser)
{
    if (animationSkipper >= 24)
    {
        if (animationIncreaser == false)
        {
            animationIndex--;
            if (animationIndex < 1)
            {
                animationIndex = 250;
            }
        }
        else if (animationIncreaser == true)
        {
            animationIndex++;
            if (animationIndex > 250)
            {
                animationIndex = 1;
            }
        }
        animationSkipper = 0;
    }
}
void InitTema2::DetectInput()
{
    // If right click is not pressed
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 forwardDir = glm::normalize(glm::vec3(cos(tankRotate.y), 0, -sin(tankRotate.y)));
        float moveSpeed = 0.007f;
        float moveSpeedFast = 0.030f;
        float moveSpeedSlow = 0.005f;
        bool animationIncreaser = false;
        wheelTilt.y = 0;

        if (window->KeyHold(GLFW_KEY_W))
        {
            animationSkipper += 2;
            tankTranslate += moveSpeed * forwardDir;
            camera->MoveForward(moveSpeed);
        }

        // If we press R, translate the tank forward faster
        if (window->KeyHold(GLFW_KEY_R))
        {
            animationSkipper += 8;
            tankTranslate += moveSpeedFast * forwardDir;
            camera->MoveForward(moveSpeedFast);
        }

        // If we press S, decrease the animation index
        if (window->KeyHold(GLFW_KEY_S))
        {
            tankTranslate += moveSpeedSlow * -forwardDir;
            animationSkipper++;
            animationIncreaser = true;
            camera->MoveForward(-moveSpeedSlow);
        }

        const float cameraDistance = camera->distanceToTarget;
        float cameraDistanceBehind = glm::length(glm::vec3(-5, 2.5f, 0)); // The desired distance behind the tank
        float cameraHeight = 2.5f; // The height offset from the tank


        const float horizontalDistance = glm::length(glm::vec3(camera->position.x - tankTranslate.x, 0, camera->position.z - tankTranslate.z)); // Horizontal distance from camera to tank
        const float verticalDistance = camera->position.y - tankTranslate.y; // Vertical distance from camera to tank
        const float initialPitchAngle = atan2(verticalDistance, horizontalDistance); // Pitch angle of the camera relative to the tank

        // Calculate the look-at point before rotation
        glm::vec3 lookAtPoint = camera->position + camera->forward * camera->distanceToTarget;

        // On key A, rotate the tank to the left
        if (window->KeyHold(GLFW_KEY_A))
        {
            tankRotate.y += moveSpeedSlow;
            wheelTilt.y = 0.3f;
            animationSkipper++;
            camera->RotateThirdPerson_OY(moveSpeedSlow, tankTranslate);
        }
        // On key D, rotate the tank to the right
        if (window->KeyHold(GLFW_KEY_D))
        {
            tankRotate.y -= moveSpeedSlow;
            wheelTilt.y = -0.3f;
            animationSkipper++;
            camera->RotateThirdPerson_OY(-moveSpeedSlow, tankTranslate);
        }

        UpdateAnimationTrackers(animationIncreaser);
    }
}

glm::vec3 m1::InitTema2::ComputeRotationBasedOnMouse()
{
    glm::vec3 rotation = glm::vec3(0, 0, 0);

    double mouseX = window->GetCursorPosition().x;
    double mouseY = window->GetCursorPosition().y;

    glm::ivec2 resolution = window->GetResolution();

    float normalizedX = (float)(mouseX - resolution.x / 2) / (resolution.x / 2);

    constexpr float maxRotationRadians = glm::half_pi<float>(); // π/2
    rotation.y = glm::clamp(normalizedX, -1.0f, 1.0f) * maxRotationRadians;

    // Assuming we don't want to rotate around the X or Z axis based on mouse position
    rotation.x = 0;
    rotation.z = 0;

    return rotation;
}

void m1::InitTema2::PositionCameraThirdPerson(int deltaX, int deltaY)
{
    float sensivityOX = 0.001f;
    float sensivityOY = 0.001f;

    camera->RotateThirdPerson_OX(-sensivityOX * deltaY);
    camera->RotateThirdPerson_OY(-sensivityOY * deltaX);
}

void InitTema2::Update(float deltaTimeSeconds)
{
    RenderTankEntity();
    DetectInput();
}



void InitTema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void InitTema2::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_1))
    {
        fov += deltaTime * cameraSpeed;
        if (fov > 150.0f)
        {
            fov = 150.0f;
        }
        projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 100.f);
        
    }

    if (window->KeyHold(GLFW_KEY_2))
    {
        fov -= deltaTime * cameraSpeed;
        if (fov < 20.0f)
        {
            fov = 20.0f;
        }
        projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 100.f);
    }
}


void InitTema2::OnKeyPress(int key, int mods)
{
}


void InitTema2::OnKeyRelease(int key, int mods)
{
}


void InitTema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 100.f);
    PositionCameraThirdPerson(deltaX, deltaY);
}


void InitTema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}


void InitTema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void InitTema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void InitTema2::OnWindowResize(int width, int height)
{
}