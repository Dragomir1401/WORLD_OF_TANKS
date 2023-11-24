#include "lab_m1/tema2/Init.hpp"

#include <vector>
#include <string>
#include <iostream>

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
    const string sourceTextureDir = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "textures");

    // Create a texture object for tank_green
    Texture2D* texture = new Texture2D();
    texture->Load2D(PATH_JOIN(sourceTextureDir, "tank_green.png").c_str(), GL_REPEAT);
    textures["tank_green"] = texture;
}

void InitTema2::RenderMeshTexture(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetProjectionMatrix()));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    //// Set any other shader uniforms that you need
    int loc_texture_1 = glGetUniformLocation(shader->program, "texture_1");
    int loc_texture_2 = glGetUniformLocation(shader->program, "texture_2");

    if (texture1)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(loc_texture_1, 0);
    }

    if (texture2)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
        glUniform1i(loc_texture_2, 1);
    }

    mesh->Render();
}

void InitTema2::RenderTexturedMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Set any other shader uniforms that you need
    int loc_texture_1 = glGetUniformLocation(shader->program, "texture_1");
    int loc_texture_2 = glGetUniformLocation(shader->program, "texture_2");

    if (texture1)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(loc_texture_1, 0);
    }

    if (texture2)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
        glUniform1i(loc_texture_2, 1);
    }

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
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
       glm::mat4 modelMatrix = glm::mat4(1);
       modelMatrix = glm::scale(modelMatrix, glm::vec3(tankScale));
       modelMatrix = glm::translate(modelMatrix, tankAdjustedTranslate);
       modelMatrix = glm::rotate(modelMatrix, tankAdjustedRotate.y, glm::vec3(0, 1, 0));
       RenderMesh(tankObjects["turet"], shaders["ShaderTank"], modelMatrix);
   }

   {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(tankScale));
        modelMatrix = glm::translate(modelMatrix, tankAdjustedTranslate);
        modelMatrix = glm::rotate(modelMatrix, tankAdjustedRotate.y, glm::vec3(0, 1, 0));
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
       modelMatrix = glm::translate(modelMatrix, glm::vec3(3.4f, -0.39f, 0.35f));
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
       modelMatrix = glm::translate(modelMatrix, glm::vec3(0.9f, -0.42f, 0.35f));
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
       modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.6f, -0.42f, 0.35f));
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
	   modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.7f, -0.42f, 0.35f));
       modelMatrix = glm::rotate(modelMatrix, wheelAdjustedTilt.y, glm::vec3(0, 1, 0));
       RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
   }
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


void InitTema2::Update(float deltaTimeSeconds)
{
    RenderTankEntity();

    // If right click is not pressed
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 forwardDir = glm::vec3(cos(tankRotate.y), 0, -sin(tankRotate.y));
        forwardDir = glm::normalize(forwardDir);

        // Movement speed
        float moveSpeed = 0.007f;
        float moveSpeedFast = 0.030f;
        float moveSpeedSlow = 0.005f;

        bool animationIncreaser = false;
        wheelTilt.y = 0;
        // If we press W, translate the tank forward
        if (window->KeyHold(GLFW_KEY_W))
        {
            animationSkipper += 2;
            tankTranslate += moveSpeed * forwardDir;
        }

        // If we press R, translate the tank forward faster
        if (window->KeyHold(GLFW_KEY_R))
        {
            animationSkipper += 8;
            tankTranslate += moveSpeedFast * forwardDir;
        }

        // If we press S, decrease the animation index
        if (window->KeyHold(GLFW_KEY_S))
        {
            tankTranslate += moveSpeedSlow * -forwardDir;
            animationSkipper++;
            animationIncreaser = true;
        }

        // On key A, rotate the tank to the left
        if (window->KeyHold(GLFW_KEY_A))
        {
            tankRotate.y += moveSpeedSlow;
            wheelTilt.y = 0.3f;
            animationSkipper++;
        }

        // On key D, rotate the tank to the right
        if (window->KeyHold(GLFW_KEY_D))
        {
            tankRotate.y -= moveSpeedSlow;
            wheelTilt.y = -0.3f;
            animationSkipper++;
        }

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
}



void InitTema2::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void InitTema2::OnInputUpdate(float deltaTime, int mods)
{
    // Add key press event
}


void InitTema2::OnKeyPress(int key, int mods)
{
    // On "W" press increase the animation index
   
}


void InitTema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void InitTema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void InitTema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void InitTema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void InitTema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void InitTema2::OnWindowResize(int width, int height)
{
}