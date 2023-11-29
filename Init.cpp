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
        for (int i = 0; i < numberOfEnemyTanks; i++)
        {
            glm::vec3 initialPosition = building->FindRandomPositionOutsideOfBuilding();
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

void m1::InitTema2::CreateSkyEntity()
{
    const string sourceObjDirSky = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "sky");
    {
		Mesh* mesh = new Mesh("sky");
		mesh->LoadMesh(sourceObjDirSky, "sky.obj");
		skyObjects["sky"] = mesh;
	}

	sky = new Sky(skyObjects);
}

void m1::InitTema2::CreateBuildingEntity()
{
    const string sourceObjDirCottage1 = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "buildings", "cottage1");
    {
        Mesh* mesh = new Mesh("cottage1");
        mesh->LoadMesh(sourceObjDirCottage1, "Cottage.obj");
        buildingObjects["cottage1"] = mesh;
    }

    const string sourceObjDirCottage2 = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "buildings", "cottage2");
    {
        Mesh* mesh = new Mesh("cottage2");
        mesh->LoadMesh(sourceObjDirCottage2, "cottage.obj");
        buildingObjects["cottage2"] = mesh;
    }

    const string sourceObjDirCottage3 = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "buildings", "cottage3");
    {
        Mesh* mesh = new Mesh("cottage3");
        mesh->LoadMesh(sourceObjDirCottage3, "cottage.obj");
        buildingObjects["cottage3"] = mesh;
    }

    const string sourceObjDirCottage4 = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "buildings", "cottage4");
    {
        Mesh* mesh = new Mesh("cottage4");
        mesh->LoadMesh(sourceObjDirCottage4, "cottage.obj");
        buildingObjects["cottage4"] = mesh;
    }

    const string sourceObjDirCottage5 = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "buildings", "cottage5");
    {
        Mesh* mesh = new Mesh("cottage5");
        mesh->LoadMesh(sourceObjDirCottage5, "cottage.obj");
        buildingObjects["cottage5"] = mesh;
    }

    const string sourceObjDirChurch = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "buildings", "church");
    {
        Mesh* mesh = new Mesh("church");
        mesh->LoadMesh(sourceObjDirChurch, "church.obj");
        buildingObjects["church"] = mesh;
    }

    const string sourceObjDirTower = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "buildings", "tower");
    {
        Mesh* mesh = new Mesh("tower");
        mesh->LoadMesh(sourceObjDirTower, "tower.obj");
        buildingObjects["tower"] = mesh;
    }
    
    building = new Building(buildingObjects);
}

void m1::InitTema2::CreateExplosionEntity()
{
    const string sourceObjDirExplosion = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "explosion");
    for (int i = 1; i <= 20; i++)
    {
        string name = "explosion" + to_string(i);
        string nameObj = "explosion" + to_string(i) + ".obj";
        Mesh* mesh = new Mesh(name);
        mesh->LoadMesh(sourceObjDirExplosion, nameObj);
        explosionObjects[name] = mesh;
    }
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
    for (int i = 0; i < enemyTanks.size(); i++)
    {
        glm::vec3 turretDirection = ComputeEnemyTurretDirection(enemyTankMovements[i]->tankTranslate + enemyTanks[i]->GetInitialPosition(),
                                                                tankMovement->tankTranslate + enemyTanks[i]->GetInitialPosition());
        // moving tank to
        enemyTankPositions[i].tankWorldMatrix = enemyTanks[i]->RenderBody(shaders, enemyTankMovements[i]->tankTranslate, enemyTankMovements[i]->tankRotate);
        enemyTankPositions[i].tankCurrentPosition = enemyTankPositions[i].tankWorldMatrix[3];
        enemyTankPositions[i].turretOrientation = enemyTanks[i]->RenderTurret(shaders, enemyTankMovements[i]->tankTranslate, enemyTankMovements[i]->tankRotate, turretDirection);
        enemyTanks[i]->RenderTun(shaders, enemyTankMovements[i]->tankTranslate, enemyTankMovements[i]->tankRotate, turretDirection);
        enemyTanks[i]->RenderWheels(shaders, enemyTankMovements[i]->tankTranslate, enemyTankMovements[i]->tankRotate, enemyTankMovements[i]->wheelTilt, enemyTankMovements[i]->animationIndex);
	}
}

void m1::InitTema2::RenderExplosions()
{
    // for every explosion
    for (int i = 0; i < explosions.size(); i++)
	{
		// render the explosion
        bool res = explosions[i]->RendExplosion(shaders);
		if (res == false)
		{
			explosions.erase(explosions.begin() + i);
		}
	}
}

void m1::InitTema2::RenderMesh(
    Mesh* mesh, 
    Shader* shader,
    const glm::mat4& modelMatrix,
    float damageGrade)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Set the damage intensity uniform
    if (damageGrade > 0)
    {
        GLint damageIntensityLoc = glGetUniformLocation(shader->program, "damageIntensity");
        float damageIntensity = damageGrade / 10.0f;
        glUniform1f(damageIntensityLoc, damageIntensity);
    }
    else
    {
		GLint damageIntensityLoc = glGetUniformLocation(shader->program, "damageIntensity");
		glUniform1f(damageIntensityLoc, 0.0f);
    }

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

void m1::InitTema2::RenderSky()
{
    sky->RenderSky(shaders);
}

void m1::InitTema2::RenderBuildings()
{
    building->RenderBuilding(shaders);
}

void InitTema2::Init()
{
    CreateGroundEntity();
    CreateBuildingEntity();
    CreateSkyEntity();
    CreateTankEntity(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "tank", "myTank"), false);   
    CreateEmemyTankEntity();
    CreateProjectileEntity();
    CreateExplosionEntity();

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
    float moveSpeed = 0.09f;
    float moveSpeedFast = 0.20f;
    float moveSpeedSlow = 0.05f;
    float moveSpeedTurn = 0.03f;

    tankMovement->wheelTilt.y = 0;

    if (window->KeyHold(GLFW_KEY_W))
    {
        tankMovement->animationSkipper += 2;
        tankMovement->tankTranslate += moveSpeed * forwardDir;
        if (!tank->CheckTankBuildingCollision(building, tankMovement->tankTranslate))
        {
            if (!tank->CheckTankEnemyTanksCollision(enemyTanks, enemyTankMovements, tankMovement->tankTranslate))
            {
			    camera->MoveForward(moveSpeed);
            }
		}
        else
        {
            tankMovement->animationSkipper -= 2;
            tankMovement->tankTranslate -= moveSpeed * forwardDir;
        }
    }

    if (window->KeyHold(GLFW_KEY_R))
    {
        tankMovement->animationSkipper += 8;
        tankMovement->tankTranslate += moveSpeedFast * forwardDir;
        if (!tank->CheckTankBuildingCollision(building, tankMovement->tankTranslate))
        {
            if (!tank->CheckTankEnemyTanksCollision(enemyTanks, enemyTankMovements, tankMovement->tankTranslate))
            {
                camera->MoveForward(moveSpeedFast);
            }
        }
        else
        {
			tankMovement->animationSkipper -= 8;
			tankMovement->tankTranslate -= moveSpeedFast * forwardDir;
		}
    }

    if (window->KeyHold(GLFW_KEY_S))
    {
        tankMovement->tankTranslate += moveSpeedSlow * -forwardDir;
        tankMovement->animationSkipper++;
        tankMovement->animationIncreaser = true;
        if (!tank->CheckTankBuildingCollision(building, tankMovement->tankTranslate))
        {
            if (!tank->CheckTankEnemyTanksCollision(enemyTanks, enemyTankMovements, tankMovement->tankTranslate))
            {
                camera->MoveForward(-moveSpeedSlow);
            }
		}
        else
        {
			tankMovement->animationSkipper--;
			tankMovement->tankTranslate -= moveSpeedSlow * -forwardDir;
            tankMovement->animationIncreaser = false;
		}
    }

    if (window->KeyHold(GLFW_KEY_A))
    {
        tankMovement->tankRotate.y += moveSpeedTurn;
        tankMovement->wheelTilt.y = 0.3f;
        tankMovement->animationSkipper++;
        camera->RotateThirdPerson_OY(moveSpeedTurn, tankMovement->tankTranslate);
    }

    if (window->KeyHold(GLFW_KEY_D))
    {
        tankMovement->tankRotate.y -= moveSpeedTurn;
        tankMovement->wheelTilt.y = -0.3f;
        tankMovement->animationSkipper++;
        camera->RotateThirdPerson_OY(-moveSpeedTurn, tankMovement->tankTranslate);
    }
    UpdateAnimationTrackers(tankMovement->animationIncreaser, tankMovement);
}

void m1::InitTema2::UpdateBasedOnTankTankCollision()
{
    for (int i = 0; i < enemyTanks.size(); i++)
	{
		if (tank->CheckTankTankCollision(enemyTanks[i], tankMovement->tankTranslate, enemyTankMovements[i]->tankTranslate))
		{
			glm::vec3 diff = tankMovement->tankTranslate - enemyTankMovements[i]->tankTranslate;
            float distance = glm::distance(tankMovement->tankTranslate, enemyTankMovements[i]->tankTranslate);
            float PF = tank->GetTankRadius() + enemyTanks[i]->GetTankRadius() - distance;
            glm::vec3 P = PF * glm::normalize(diff);
            glm::vec3 displacement = P * -0.5f;
            tankMovement->tankTranslate += P * -0.5f;
            enemyTankMovements[i]->tankTranslate += P * 0.5f;

            camera->SetPosition(camera->GetPosition() + displacement);
		}
	}
}

bool m1::InitTema2::CheckBulletBuildingCollision(m1::Bullet* bullet)
{
    // For each building
    for (int i = 0; i < building->GetBuildingPositions().size(); i++)
	{
        float buildingRadius = building->GetBuildingRadiusPerType()[building->GetBuildingTypes()[i]];
        float bulletRadius = bullet->GetBulletRadius();

        float distanceBetweenTankAndBuilding = glm::distance(bullet->GetBulletPosition(), building->GetBuildingPositions()[i]);

        if (distanceBetweenTankAndBuilding < buildingRadius + bulletRadius)
		{
            building->DamageBuilding(i);
			return true;
		}
	}

    return false;
}

void m1::InitTema2::CheckAllBulletsBuildingCollisions()
{
    // For each bullet
    for (int i = 0; i < bullets.size(); i++)
	{
		if (CheckBulletBuildingCollision(bullets[i]))
		{
            Explosion* explosion = new Explosion(
                                    explosionObjects,
                                    bullets[i]->GetBulletPosition());
            explosions.push_back(explosion);

			bullets.erase(bullets.begin() + i);
		}
	}
}

bool m1::InitTema2::CheckBulletTankCollision(m1::Bullet* bullet)
{
    // For each enemy tank
    for (int i = 0; i < enemyTanks.size(); i++)
    {
		float tankRadius = enemyTanks[i]->GetTankRadius();
		float bulletRadius = bullet->GetBulletRadius();

		float distanceBetweenTankAndBullet = glm::distance(bullet->GetBulletPosition(),
            enemyTankMovements[i]->tankTranslate + enemyTanks[i]->GetInitialPosition());

		if (distanceBetweenTankAndBullet < tankRadius + bulletRadius)
		{
            enemyTanks[i]->Damage();
            if (enemyTanks[i]->GetDamage() > enemyTanks[i]->GetMaxDamage())
            {
				enemyTanks.erase(enemyTanks.begin() + i);
				enemyTankMovements.erase(enemyTankMovements.begin() + i);
				enemyTankPositions.erase(enemyTankPositions.begin() + i);
            }
			return true;
		}
	}

	return false;
}

void m1::InitTema2::CheckAllBulletsTankCollisions()
{
    // For each bullet
	for (int i = 0; i < bullets.size(); i++)
	{
		if (CheckBulletTankCollision(bullets[i]))
		{
			Explosion* explosion = new Explosion(
				explosionObjects,
				bullets[i]->GetBulletPosition());
			explosions.push_back(explosion);

			bullets.erase(bullets.begin() + i);
		}
	}
}

glm::vec3 m1::InitTema2::ComputeEnemyTurretDirection(glm::vec3 enemyTankPosition, glm::vec3 playerTankPosition) {
    // Compute the direction vector from enemy to player
    glm::vec3 direction = playerTankPosition - enemyTankPosition;

    // Normalize the direction vector to get a unit vector
    direction = glm::normalize(direction);

    // Calculate the rotation angle around the Y-axis to face the player tank
    float rotationAngle = atan2(-direction.z, direction.x);

    // Convert rotation angle to degrees if necessary (assuming your engine uses degrees)
    rotationAngle = glm::degrees(rotationAngle);

    // Normalize angle to [0, 360) range or whatever range your game engine uses
    rotationAngle = fmod(rotationAngle + 360.0f, 360.0f);

    return glm::vec3(0.0f, rotationAngle, 0.0f); // Assuming rotation is around the Y axis
}



void m1::InitTema2::RandomizeEnemyTankMovement(float deltaTime) {
    glm::vec3 myTankPosition = tankPosition.tankCurrentPosition;
    float moveSpeed = 0.7f;

    for (int i = 0; i < enemyTanks.size(); i++)
    {
        //enemyTankMovements[i]->UpdateMovementState(enemyTankPositions[i].tankCurrentPosition, myTankPosition);

        enemyTankMovements[i]->tankState = TankMovement::TankState::Idle;
        switch (enemyTankMovements[i]->tankState)
        {
        case m1::TankMovement::TankState::Chase:
            enemyTankMovements[i]->MoveTowards(myTankPosition, moveSpeed, deltaTime, enemyTankPositions[i].tankCurrentPosition);
            break;
        case m1::TankMovement::TankState::Flee:
            enemyTankMovements[i]->MoveAway(myTankPosition, moveSpeed, deltaTime, enemyTankPositions[i].tankCurrentPosition);
            break;
        case m1::TankMovement::TankState::Idle:
            enemyTankMovements[i]->IdleMove(currentTime, enemyTanks[i], building);
            break;
        default:
            enemyTankMovements[i]->IdleMove(currentTime, enemyTanks[i], building);
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
    RenderGround();
    RenderBuildings();
    RenderSky();

    RandomizeEnemyTankMovement(deltaTimeSeconds);
    DetectInput();
    UpdateBasedOnTankTankCollision();

    RenderEnemyTankEntity();
    RenderTankEntity();

    ShootOnLeftClick();
    MoveBulletsInLine();

    CheckAllBulletsBuildingCollisions();
    CheckAllBulletsTankCollisions();
    RenderExplosions();

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