#include "lab_m1/tema2/Init.hpp"

#include <vector>
#include <string>
#include <iostream>
#include "init.hpp"

using namespace std;
using namespace m1;

glm::mat4 m1::InitTema2::projectionMatrix;
m1::Camera* m1::InitTema2::camera;


InitTema2::InitTema2()
{
}


InitTema2::~InitTema2()
{
}

void m1::InitTema2::CreateTankEntity(string sourceObjDirTank, bool isEnemy)
{
    {
        Mesh* mesh = new Mesh("body");
        mesh->LoadMesh(sourceObjDirTank, "body.obj");
       
        if (!isEnemy)
        {
            tankObjects["body"] = mesh;
        }
        else
        {
            enemyTankObjects["body"] = mesh;
        }
    }

    {
		Mesh* mesh = new Mesh("tun");
		mesh->LoadMesh(sourceObjDirTank, "tunGun.obj");
		
        if (!isEnemy)
        {
			tankObjects["tun"] = mesh;
		}
        else
        {
			enemyTankObjects["tun"] = mesh;
		}
	}

    {
        Mesh* mesh = new Mesh("turet");
        mesh->LoadMesh(sourceObjDirTank, "tun.obj");

        if (!isEnemy)
        {
            tankObjects["turet"] = mesh;
        }
        else
        {
			enemyTankObjects["turet"] = mesh;
		}
    }

    for (int i = 1; i <= 250; i++)
    {
		string name = "wheel" + to_string(i);
		string nameObj = "wheel" + to_string(i) + ".obj";
		Mesh* mesh = new Mesh(name);
		mesh->LoadMesh(sourceObjDirTank, nameObj);

        if (!isEnemy)
        {
			tankObjects[name] = mesh;
		}
        else
        {
			enemyTankObjects[name] = mesh;
		}
	}

    if (!isEnemy)
    {
        tank = new Tank(tankObjects, glm::vec3(0, 0, 0));

        tankMovement = new TankMovement(
			glm::vec3(0, 0, 0),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 0, 0),
			0,
			250,
			false,
			m1::TankMovement::TankState::Idle);
    }
    else
    {
        for (int i = 0; i < NUM_ENEMY_TANKS; i++)
        {
			glm::vec3 initialPosition = glm::vec3(0, 0, 0);
            initialPosition.x = (float)(rand() % 15);
			initialPosition.z = (float)(rand() % 15);
			Tank* enemyTank = new Tank(enemyTankObjects, initialPosition);
			enemyTanks.push_back(enemyTank);

            TankMovement* enemyTankMovement = new TankMovement(
                                                initialPosition,
                                                glm::vec3(0, 0, 0),
                                                glm::vec3(0, 0, 0),
                                                0,
                                                250,
                                                false,
                                                m1::TankMovement::TankState::Idle);
            enemyTankMovements.push_back(enemyTankMovement);

            TankPosition enemyTankPosition;
            enemyTankPosition.tankWorldMatrix = glm::mat4(1);
            enemyTankPosition.tankCurrentPosition = initialPosition;
            enemyTankPosition.turretOrientation = TurretOrientation();
            enemyTankPositions.push_back(enemyTankPosition);
		}
	}
}


void m1::InitTema2::CreateEmemyTankEntity()
{
    string sourceObjDirEnemyTank = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "tank", "enemyTank");
	CreateTankEntity(sourceObjDirEnemyTank, true);
}

void InitTema2::CreateProjectileEntity()
{
    const string sourceObjDirProjectiles = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "projectile");
    for (int i = 1; i <= 60; i++)
    {
        string name = "projectile" + to_string(i);
        string nameObj = "projectile" + to_string(i) + ".obj";
        Mesh* mesh = new Mesh(name);
        mesh->LoadMesh(sourceObjDirProjectiles, nameObj);
        projectileObjects[name] = mesh;
    }
}

void InitTema2::CreateGroundEntity()
{
    const string sourceObjDirGround = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "ground");
    {
        Mesh* mesh = new Mesh("ground");
        mesh->LoadMesh(sourceObjDirGround, "ground.obj");
        groundObjects["ground"] = mesh;
    }

    ground = new Ground(groundObjects);
}

void m1::InitTema2::RenderTankEntity()
{
    tankPosition.tankWorldMatrix = tank->RenderBody(shaders, tankMovement->tankTranslate, tankMovement->tankRotate);
    tankPosition.tankCurrentPosition = tankPosition.tankWorldMatrix[3];
    tankPosition.turretOrientation = tank->RenderTurret(shaders, tankMovement->tankTranslate, tankMovement->tankRotate, ComputeRotationBasedOnMouse());
    tank->RenderTun(shaders, tankMovement->tankTranslate, tankMovement->tankRotate, ComputeRotationBasedOnMouse());
    tank->RenderWheels(shaders, tankMovement->tankTranslate, tankMovement->tankRotate, tankMovement->wheelTilt, tankMovement->animationIndex);
}

void m1::InitTema2::RenderEnemyTankEntity()
{
    for (int i = 0; i < NUM_ENEMY_TANKS; i++)
    {
        enemyTankPositions[i].tankWorldMatrix = enemyTanks[i]->RenderBody(shaders, enemyTankMovements[i]->tankTranslate, enemyTankMovements[i]->tankRotate);
        enemyTankPositions[i].tankCurrentPosition = enemyTankPositions[i].tankWorldMatrix[3];
        enemyTankPositions[i].turretOrientation = enemyTanks[i]->RenderTurret(shaders, enemyTankMovements[i]->tankTranslate, enemyTankMovements[i]->tankRotate, ComputeRotationBasedOnMouse());
        enemyTanks[i]->RenderTun(shaders, enemyTankMovements[i]->tankTranslate, enemyTankMovements[i]->tankRotate, ComputeRotationBasedOnMouse());
        enemyTanks[i]->RenderWheels(shaders, enemyTankMovements[i]->tankTranslate, enemyTankMovements[i]->tankRotate, enemyTankMovements[i]->wheelTilt, enemyTankMovements[i]->animationIndex);

        //cout << "Enemy tank position: " << enemyTankPositions[i].tankCurrentPosition.x << " " << enemyTankPositions[i].tankCurrentPosition.y << " " << enemyTankPositions[i].tankCurrentPosition.z << endl;
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

void m1::InitTema2::ShootOnLeftClick()
{
    // Render the projectile at the tip of the tun when clicking left mouse button
    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT) && currentTime - lastTimeShot > 2.0f)
    {
        glm::vec3 mouseRotation = ComputeRotationBasedOnMouse();
        Bullet* bullet = new Bullet(
            tankPosition.tankCurrentPosition,
            projectileObjects,
            1,
            tankMovement->tankRotate,
            tankPosition.tankWorldMatrix,
            mouseRotation,
            tankPosition.turretOrientation.turretRelativeRotationWhenBulletWasShot,
            tankPosition.turretOrientation.turretWorldMatrixWhenBulletWasShot,
            currentTime);

        bullets.push_back(bullet);
        lastTimeShot = currentTime;
    }
}

void m1::InitTema2::MoveBulletsInLine()
{
    for (auto &bullet : bullets)
    {
        bool res = bullet->RendBullet(currentTime, shaders);
        if (res == false)
		{
			bullets.erase(bullets.begin());
		}
	}
}

void m1::InitTema2::RenderGround()
{
    ground->RenderGround(shaders);
}

void InitTema2::Init()
{
    CreateTankEntity(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "tank", "myTank"), false);   
    CreateEmemyTankEntity();
    CreateProjectileEntity();
    CreateGroundEntity();

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
    projectionMatrix = glm::perspective(RADIANS(90), window->props.aspectRatio, 0.01f, 200.0f);
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

void InitTema2::UpdateAnimationTrackers(bool &animationIncreaser, TankMovement* tankMovement)
{
    if (tankMovement->animationSkipper >= 16)
    {
        if (tankMovement->animationIncreaser == false)
        {
            tankMovement->animationIndex--;
            if (tankMovement->animationIndex < 1)
            {
                tankMovement->animationIndex = 250;
            }
        }
        else if (animationIncreaser == true)
        {
            tankMovement->animationIndex++;
            if (tankMovement->animationIndex > 250)
            {
                tankMovement->animationIndex = 1;
            }
        }
        tankMovement->animationSkipper = 0;
    }
}

void InitTema2::DetectInput()
{
    glm::vec3 forwardDir = glm::normalize(glm::vec3(cos(tankMovement->tankRotate.y), 0, -sin(tankMovement->tankRotate.y)));
    float moveSpeed = 0.007f;
    float moveSpeedFast = 0.030f;
    float moveSpeedSlow = 0.005f;
    tankMovement->wheelTilt.y = 0;

    if (window->KeyHold(GLFW_KEY_W))
    {
        tankMovement->animationSkipper += 2;
        tankMovement->tankTranslate += moveSpeed * forwardDir;
        camera->MoveForward(moveSpeed);
    }

    if (window->KeyHold(GLFW_KEY_R))
    {
        tankMovement->animationSkipper += 8;
        tankMovement->tankTranslate += moveSpeedFast * forwardDir;
        camera->MoveForward(moveSpeedFast);
    }

    if (window->KeyHold(GLFW_KEY_S))
    {
        tankMovement->tankTranslate += moveSpeedSlow * -forwardDir;
        tankMovement->animationSkipper++;
        tankMovement->animationIncreaser = true;
        camera->MoveForward(-moveSpeedSlow);
    }

    if (window->KeyHold(GLFW_KEY_A))
    {
        tankMovement->tankRotate.y += moveSpeedSlow;
        tankMovement->wheelTilt.y = 0.3f;
        tankMovement->animationSkipper++;
        camera->RotateThirdPerson_OY(moveSpeedSlow, tankMovement->tankTranslate);
    }

    if (window->KeyHold(GLFW_KEY_D))
    {
        tankMovement->tankRotate.y -= moveSpeedSlow;
        tankMovement->wheelTilt.y = -0.3f;
        tankMovement->animationSkipper++;
        camera->RotateThirdPerson_OY(-moveSpeedSlow, tankMovement->tankTranslate);
    }
    UpdateAnimationTrackers(tankMovement->animationIncreaser, tankMovement);
}

void m1::InitTema2::RandomizeEnemyTankMovement(float deltaTime) {
    glm::vec3 myTankPosition = tankPosition.tankCurrentPosition;
    float moveSpeed = 0.007f;

    for (int i = 0; i < NUM_ENEMY_TANKS; i++)
    {
        enemyTankMovements[i]->UpdateMovementState(enemyTankPositions[i].tankCurrentPosition, myTankPosition);

        switch (enemyTankMovements[i]->tankState)
        {
        case m1::TankMovement::TankState::Chase:
            enemyTankMovements[i]->MoveTowards(myTankPosition, moveSpeed, deltaTime, enemyTankPositions[i].tankCurrentPosition);
            break;
        case m1::TankMovement::TankState::Flee:
            enemyTankMovements[i]->MoveAway(myTankPosition, moveSpeed, deltaTime, enemyTankPositions[i].tankCurrentPosition);
            break;
        case m1::TankMovement::TankState::Idle:
            // Perform idle behavior like random rotations
            enemyTankMovements[i]->RotateRandomly(deltaTime);
            break;
        }

        // Update animation trackers for the movement
        UpdateAnimationTrackers(enemyTankMovements[i]->animationIncreaser, enemyTankMovements[i]);
    }
}


glm::vec3 m1::InitTema2::ComputeRotationBasedOnMouse()
{
    glm::vec3 rotation = glm::vec3(0, 0, 0);

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
		return lastTuretRotation;
	}

    double mouseX = window->GetCursorPosition().x;
    double mouseY = window->GetCursorPosition().y;

    glm::ivec2 resolution = window->GetResolution();

    float normalizedX = (float)(mouseX - resolution.x / 2) / (resolution.x / 2);

    constexpr float maxRotationRadians = glm::half_pi<float>(); // π/2
    rotation.y = glm::clamp(normalizedX, -1.0f, 1.0f) * maxRotationRadians;

    rotation.x = 0;
    rotation.z = 0;

    lastTuretRotation = rotation;

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
    RenderEnemyTankEntity();
    RandomizeEnemyTankMovement(deltaTimeSeconds);
    DetectInput();
    ShootOnLeftClick();
    MoveBulletsInLine();
    RenderGround();

    currentTime += deltaTimeSeconds;
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
        if (fov > 175.0f)
        {
            fov = 175.0f;
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