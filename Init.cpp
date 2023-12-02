#include "lab_m1/tema2/Init.hpp"

#include <vector>
#include <string>
#include <iostream>
#include "init.hpp"

using namespace std;
using namespace m1;

glm::mat4 m1::InitTema2::projectionMatrix;
glm::mat4 m1::InitTema2::projectionMatrixMiniMap;
glm::mat4 m1::InitTema2::viewMatrix;
glm::mat4 m1::InitTema2::viewMatrixMiniMap;
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

void m1::InitTema2::CreateHelicopterEntity()
{
    string sourceObjDirHelicopter = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "helicopter");

    {
        Mesh* mesh = new Mesh("body");
        mesh->LoadMesh(sourceObjDirHelicopter, "body.obj");
        helicopterObjects["body"] = mesh;
    }

    for (int i = 1; i <= 10; i++)
    {
		string name = "blade" + to_string(i);
		string nameObj = "blade" + to_string(i) + ".obj";
		Mesh* mesh = new Mesh(name);
		mesh->LoadMesh(sourceObjDirHelicopter, nameObj);
		helicopterObjects[name] = mesh;
    }

    for (int i = 1; i <= 10; i++)
    {
        string name = "backBlade" + to_string(i);
        string nameObj = "backBlade" + to_string(i) + ".obj";
        Mesh* mesh = new Mesh(name);
        mesh->LoadMesh(sourceObjDirHelicopter, nameObj);
        helicopterObjects[name] = mesh;
    }

    helicopterMovement = new TankMovement(
		glm::vec3(0, helicopterHeightOfFlying, 0),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0, 0),
		0,
		1,
		false,
		m1::TankMovement::TankState::Idle);

    helicopterPosition.tankWorldMatrix = glm::mat4(1);
    helicopterPosition.tankCurrentPosition = glm::vec3(0, 0, 0);
    helicopterPosition.turretOrientation = TurretOrientation();

    helicopter = new Helicopter(helicopterObjects, glm::vec3(0, helicopterHeightOfFlying, 0));
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

void m1::InitTema2::CreateMenuEntity(glm::ivec2 resolution)
{
    const string sourceObjDirMenu = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "menu");
    {
		Mesh* mesh = new Mesh("menu");
		mesh->LoadMesh(sourceObjDirMenu, "background.obj");
		menuObjects["background"] = mesh;
	}

    {
        Mesh* mesh = new Mesh("button");
        mesh->LoadMesh(sourceObjDirMenu, "button.obj");
        menuObjects["button"] = mesh;
    }

    textRenderer = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);
    textRenderer->Load(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"), 18);
	menu = new Menu(menuObjects, textRenderer, resolution);
}

void m1::InitTema2::CreateStatsTextEntity(glm::ivec2 resolution)
{
    statsRenderer = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);
    statsRenderer->Load(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"), 18);

    statsText = new StatsText(statsRenderer, resolution);
}

void m1::InitTema2::LoadSounds()
{
    const string sourceObjDirSounds = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "sounds");
    {
		Audio* audio = new Audio(sourceObjDirSounds + "/music.wav", MUSIC);
        sounds.push_back(audio);

        audio = new Audio(sourceObjDirSounds + "/engineIdle.wav", ENGINE_IDLE);
        sounds.push_back(audio);

        audio = new Audio(sourceObjDirSounds + "/engineWorking.wav", ENGINE_WORKING);
        sounds.push_back(audio);

        audio = new Audio(sourceObjDirSounds + "/shoot.wav", SHOOT);
        sounds.push_back(audio);

        audio = new Audio(sourceObjDirSounds + "/explosionCloseRange.wav", EXPLOSION_CLOSE);
        sounds.push_back(audio);

        audio = new Audio(sourceObjDirSounds + "/explosionMidRange.wav", EXPLOSION_MID);
        sounds.push_back(audio);

        audio = new Audio(sourceObjDirSounds + "/explosionLongRange.wav", EXPLOSION_FAR);
        sounds.push_back(audio);

        audio = new Audio(sourceObjDirSounds + "/fatality.wav", FATALITY);
        sounds.push_back(audio);

        audio = new Audio(sourceObjDirSounds + "/died.wav", DIED);
        sounds.push_back(audio);

        audio = new Audio(sourceObjDirSounds + "/helicopter.wav", HELICOPTER);
        sounds.push_back(audio);
	}
}

void m1::InitTema2::RenderTankEntity(bool minimap)
{
    tankPosition.tankWorldMatrix = tank->RenderBody(
        shaders, 
        tankMovement->tankTranslate,
        tankMovement->tankRotate,
        minimap);

    glm::vec3 mouseRotation = ComputeRotationBasedOnMouse();
    if (helicopterPerspective)
    {
        mouseRotation = glm::vec3(0, 0, 0);
    }

    tankPosition.tankCurrentPosition = tankPosition.tankWorldMatrix[3];
    tankPosition.turretOrientation = tank->RenderTurret(
        shaders,
        tankMovement->tankTranslate,
        tankMovement->tankRotate,
        mouseRotation,
        minimap);

    tank->RenderTun(
        shaders, 
        tankMovement->tankTranslate,
        tankMovement->tankRotate, 
        mouseRotation,
        minimap);

    tank->RenderWheels(
        shaders, 
        tankMovement->tankTranslate, 
        tankMovement->tankRotate, 
        tankMovement->wheelTilt,
        tankMovement->animationIndex, 
        minimap);
}

void m1::InitTema2::RenderHelicopterEntity(bool minimap)
{
    helicopterPosition.tankWorldMatrix = helicopter->RenderBody(
		shaders,
		helicopterMovement->tankTranslate,
        helicopterMovement->tankRotate,
		minimap);
    helicopterPosition.tankCurrentPosition = helicopterPosition.tankWorldMatrix[3];

    helicopter->RenderBlade(
		shaders,
        helicopterMovement->tankTranslate,
        helicopterMovement->tankRotate,
        helicopterMovement->animationIndex,
		minimap);

    helicopter->RenderBackBlade(
        shaders,
        helicopterMovement->tankTranslate,
        helicopterMovement->tankRotate,
        helicopterMovement->animationIndex,
        minimap);
}

float NormalizeAngle(float angle) {
    angle = (float)fmod(angle, 2 * M_PI);
    if (angle < 0) {
        angle += (float)(2 * M_PI);
    }
    return angle;
}

void m1::InitTema2::RenderEnemyTankEntity(bool minimap)
{
    for (int i = 0; i < enemyTanks.size(); i++)
    {
        float worldTurretRotation = ComputeEnemyTurretDirection(
            enemyTankMovements[i]->tankTranslate + enemyTanks[i]->GetInitialPosition(),
            tankMovement->tankTranslate + tank->GetInitialPosition());      

        // Convert world rotation to tank-relative rotation
        float tankBodyRotationY = enemyTankMovements[i]->tankRotate.y;
        float turretRelativeRotationY = worldTurretRotation - tankBodyRotationY;

        // Normalize the turret rotation angle
        turretRelativeRotationY = NormalizeAngle(turretRelativeRotationY);

        glm::vec3 turretDirection = glm::vec3(0, turretRelativeRotationY, 0);
        // moving tank to
        enemyTankPositions[i].tankWorldMatrix = enemyTanks[i]->RenderBody(
            shaders,
            enemyTankMovements[i]->tankTranslate,
            enemyTankMovements[i]->tankRotate,
            minimap);

        enemyTankPositions[i].tankCurrentPosition = enemyTankPositions[i].tankWorldMatrix[3];
        enemyTankPositions[i].turretOrientation = enemyTanks[i]->RenderTurret(
            shaders, 
            enemyTankMovements[i]->tankTranslate,
            enemyTankMovements[i]->tankRotate, 
            turretDirection, 
            minimap);

        enemyTanks[i]->RenderTun(
            shaders, 
            enemyTankMovements[i]->tankTranslate, 
            enemyTankMovements[i]->tankRotate,
            turretDirection, 
            minimap);

        enemyTanks[i]->RenderWheels(
            shaders, 
            enemyTankMovements[i]->tankTranslate, 
            enemyTankMovements[i]->tankRotate, 
            enemyTankMovements[i]->wheelTilt, 
            enemyTankMovements[i]->animationIndex, 
            minimap);
	}
}

void m1::InitTema2::RenderExplosions(bool minimap)
{
    // for every explosion
    for (int i = 0; i < explosions.size(); i++)
	{
		// render the explosion
        bool res = explosions[i]->RendExplosion(shaders, minimap);
		if (res == false)
		{
			explosions.erase(explosions.begin() + i);
            firstExplisonFrames.erase(firstExplisonFrames.begin() + i);
		}
        else if (firstExplisonFrames[i])
        {
            // Compute distance between my tank and explosion
            float distance = glm::distance(tankMovement->tankTranslate + tank->GetInitialPosition(), explosions[i]->GetPosition());

            // Play the explosion sound based on the distance
            if (distance < 10)
            {
                sounds.at(EXPLOSION_CLOSE)->Kill();
                sounds.at(EXPLOSION_CLOSE)->Play();
            }
            else if (distance < 20)
            {
                sounds.at(EXPLOSION_MID)->Kill();
                sounds.at(EXPLOSION_MID)->Play();
            }
            else
            {
                sounds.at(EXPLOSION_FAR)->Kill();
                sounds.at(EXPLOSION_FAR)->Play();
            }

            firstExplisonFrames[i] = false;
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

void m1::InitTema2::RenderTexturedMesh(
    Mesh* mesh, 
    Shader* shader,
    const glm::mat4& modelMatrix,
    Texture2D* texture1, 
    Texture2D* texture2)
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

    // TODO(student): Set any other shader uniforms that you need
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

void m1::InitTema2::RenderMeshMinimap(
    Mesh* mesh,
    Shader* shader,
    const glm::mat4& modelMatrix,
    float damageGrade
	)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Use the specified shader
    shader->Use();

    // Set the view and projection matrices for the minimap camera
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrixMiniMap));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrixMiniMap));
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


    // Render the mesh
    mesh->Render();
}

void m1::InitTema2::ShootOnLeftClick()
{
    // Render the projectile at the tip of the tun when clicking left mouse button
    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT) && currentTime - lastTimeShot > 2.0f)
    {
        Bullet* bullet;
        if (!helicopterPerspective)
        {
            glm::vec3 mouseRotation = ComputeRotationBasedOnMouse();
            bullet = new Bullet(
                tankPosition.tankCurrentPosition,
                projectileObjects,
                1,
                tankMovement->tankRotate,
                tankPosition.tankWorldMatrix,
                mouseRotation,
                tankPosition.turretOrientation.turretRelativeRotationWhenBulletWasShot,
                tankPosition.turretOrientation.turretWorldMatrixWhenBulletWasShot,
                currentTime);
        }
        else
        {
            glm::vec3 helicopterPos = helicopterMovement->tankTranslate + helicopter->GetInitialPosition();
            bullet = new Bullet(
                helicopterPos,
				projectileObjects,
				1,
				helicopterMovement->tankRotate,
				helicopterPosition.tankWorldMatrix,
				glm::vec3(0, 0, 0),
				helicopterPosition.turretOrientation.turretRelativeRotationWhenBulletWasShot,
				helicopterPosition.turretOrientation.turretWorldMatrixWhenBulletWasShot,
				currentTime,
                true,
                0.6);
        }

        bullets.push_back(bullet);
        lastTimeShot = currentTime;

        sounds.at(SHOOT)->Kill();
        sounds.at(SHOOT)->Play();
    }
}

void m1::InitTema2::MoveBulletsInLine()
{
    for (auto &bullet : bullets)
    {
        bool res;
        if (!helicopterPerspective)
        {
            res = bullet->RendBullet(currentTime, shaders);
        }
        else
        {
            res = bullet->RendHelicopterBullet(currentTime, shaders);
        }

        if (res == false)
		{
			bullets.erase(bullets.begin());
		}
	}
}

void m1::InitTema2::RenderGround(bool minimap)
{
    if (!minimap)
    {
        ground->RenderGround(shaders);
    }
    else
    {
		ground->RenderGround(shaders, true);
	}
}

void m1::InitTema2::RenderSky()
{
    sky->RenderSky(shaders);
}

void m1::InitTema2::RenderBuildings(bool minimap)
{
    if (!minimap)
    {
		building->RenderBuilding(shaders);
	}
	else
	{
        building->RenderBuilding(shaders, true);
    }
}

void m1::InitTema2::RenderMenu()
{
    menu->RenderMenu(shaders);
}

void m1::InitTema2::RenderStatsText()
{
    statsText->RenderStatsText(shaders, kills, landedShots);
}

void InitTema2::Init()
{
    LoadSounds();
    sounds.at(MUSIC)->Play();

    if (!helicopterPerspective)
    {
        sounds.at(ENGINE_IDLE)->Play();
    }
    else
    {
        sounds.at(HELICOPTER)->Play();
    }
    CreateGroundEntity();
    CreateBuildingEntity();
    CreateSkyEntity();
    CreateTankEntity(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "objects", "tank", "myTank"), false);   
    CreateEmemyTankEntity();
    CreateProjectileEntity();
    CreateExplosionEntity();
    CreateHelicopterEntity();

    {
        Shader *shader = new Shader("ShaderTank");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "TextureVertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragTextureShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        Shader* shader = new Shader("Shader2D");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Sets the camera
    camera = new Camera();
    float distanceBehind = 5.0f;
    float elevation = 2.5f;
    glm::vec3 cameraPosition = tankMovement->tankTranslate + glm::vec3(0, elevation, 0);
    camera->Set(cameraPosition, tankMovement->tankTranslate, glm::vec3(0, 1, 0));
    initialCameraPosition = glm::vec3(-5, 2.5f, 0);
    projectionMatrix = glm::perspective(RADIANS(90), window->props.aspectRatio, 0.01f, 200.0f);
    fov = 80.0f;

    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, (int)(resolution.x / 5.f), (int)(resolution.y / 5.f));
    CreateMenuEntity(resolution);
    CreateStatsTextEntity(resolution);
}

void InitTema2::PositionCameraBehindEntity(TankMovement* movement)
{
    glm::vec3 forwardDir = glm::normalize(glm::vec3(cos(movement->tankRotate.y), 0, -sin(movement->tankRotate.y)));

    float distanceBehind = 5.0f;
    if (helicopterPerspective)
    {
		distanceBehind = 7.5f;
	}
    float elevation = 2.5f + movement->tankTranslate.y;
    if (helicopterPerspective)
    {
        elevation += 2.5f;
    }
    glm::vec3 cameraPosition = movement->tankTranslate - forwardDir * distanceBehind + glm::vec3(0, elevation, 0);

	camera->Set(cameraPosition, movement->tankTranslate, glm::vec3(0, 1, 0));
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
    glm::vec3 forwardDir;
    if (!helicopterPerspective)
    {
        forwardDir = glm::normalize(glm::vec3(cos(tankMovement->tankRotate.y), 0, -sin(tankMovement->tankRotate.y)));
        tankMovement->wheelTilt.y = 0;
    }
    else
    {
		forwardDir = glm::normalize(glm::vec3(cos(helicopterMovement->tankRotate.y), 0, -sin(helicopterMovement->tankRotate.y)));
	}
    float moveSpeed = 0.09f;
    float moveSpeedFast = 0.20f;
    float moveSpeedSlow = 0.05f;
    float moveSpeedTurn = 0.03f;

    if (window->KeyHold(GLFW_KEY_W))
    {
        if (!helicopterPerspective)
        {
            tankMovement->animationSkipper += 2;
            tankMovement->tankTranslate += moveSpeed * forwardDir;
            PositionCameraBehindEntity(tankMovement);

            if (currentTime > lastTimeEngineWorking + 3.0f)
            {
                sounds.at(ENGINE_WORKING)->Kill();
                sounds.at(ENGINE_WORKING)->Play();
                lastTimeEngineWorking = currentTime;
            }
        }
        else
        {
			helicopterMovement->tankTranslate += moveSpeed * forwardDir;
            PositionCameraBehindEntity(helicopterMovement);
        }
    }

    if (window->KeyHold(GLFW_KEY_R))
    {
        if (!helicopterPerspective)
        {
            tankMovement->animationSkipper += 8;
            tankMovement->tankTranslate += moveSpeedFast * forwardDir;
            PositionCameraBehindEntity(tankMovement);

            if (currentTime > lastTimeEngineWorking + 3.0f)
            {
                sounds.at(ENGINE_WORKING)->Kill();
                sounds.at(ENGINE_WORKING)->Play();
                lastTimeEngineWorking = currentTime;
            }
        }
        else
        {
            helicopterMovement->tankTranslate += moveSpeedFast * forwardDir;
            PositionCameraBehindEntity(helicopterMovement);
        }
    }

    if (window->KeyHold(GLFW_KEY_S))
    {
        if (!helicopterPerspective)
        {
            tankMovement->tankTranslate += moveSpeedSlow * -forwardDir;
            tankMovement->animationSkipper++;
            tankMovement->animationIncreaser = true;
            PositionCameraBehindEntity(tankMovement);
        }
        else
        {
            helicopterMovement->tankTranslate += moveSpeedSlow * -forwardDir;
			PositionCameraBehindEntity(helicopterMovement);
        }
    }

    if (window->KeyHold(GLFW_KEY_A))
    {
        if (!helicopterPerspective)
        {
            tankMovement->tankRotate.y += moveSpeedTurn;
            tankMovement->wheelTilt.y = 0.3f;
            tankMovement->animationSkipper++;
            PositionCameraBehindEntity(tankMovement);
        }
        else
        {
			helicopterMovement->tankRotate.y += moveSpeedTurn / 3;
			PositionCameraBehindEntity(helicopterMovement);
        }
    }

    if (window->KeyHold(GLFW_KEY_D))
    {
        if (!helicopterPerspective)
        {
            tankMovement->tankRotate.y -= moveSpeedTurn;
            tankMovement->wheelTilt.y = -0.3f;
            tankMovement->animationSkipper++;
            PositionCameraBehindEntity(tankMovement);
        }
        else
        {
            helicopterMovement->tankRotate.y -= moveSpeedTurn / 3;
            PositionCameraBehindEntity(helicopterMovement);
        }
    }

    if (!helicopterPerspective)
    {
        UpdateAnimationTrackers(tankMovement->animationIncreaser, tankMovement);
    }

    if (helicopterMovement->animationIndex > 10)
    {
        helicopterMovement->animationIndex = 1;
    }
    helicopterMovement->animationIndex += 1;


    if (helicopterPerspective)
    {
        if (window->KeyHold(GLFW_KEY_RIGHT))
        {
			helicopterMovement->tankRotate.x += moveSpeedTurn / 3;
        }

        if (window->KeyHold(GLFW_KEY_LEFT))
        {
            helicopterMovement->tankRotate.x -= moveSpeedTurn / 3;
        }

        if (window->KeyHold(GLFW_KEY_DOWN))
        {
			helicopterMovement->tankRotate.z += moveSpeedTurn / 3;
		}

        if (window->KeyHold(GLFW_KEY_UP))
        {
            helicopterMovement->tankRotate.z -= moveSpeedTurn / 3;
        }

        if (window->KeyHold(GLFW_KEY_N))
        {
			helicopterMovement->tankTranslate.y -= moveSpeed;
		}

        if (window->KeyHold(GLFW_KEY_M))
        {
			helicopterMovement->tankTranslate.y += moveSpeed;
		}
        PositionCameraBehindEntity(helicopterMovement);
    }
}

void m1::InitTema2::UpdateBasedOnTankTankCollision(Tank *tank, TankMovement *tankMovement, int tankId)
{
    for (int i = 0; i < enemyTanks.size(); i++)
	{
        if (i == tankId)
        {
            continue;
        }
		if (tank->CheckTankTankCollision(enemyTanks[i], tankMovement->tankTranslate, enemyTankMovements[i]->tankTranslate))
		{
			glm::vec3 diff = tankMovement->tankTranslate + tank->GetInitialPosition() -
                            (enemyTankMovements[i]->tankTranslate + enemyTanks[i]->GetInitialPosition());
            float distance = glm::distance(tankMovement->tankTranslate + tank->GetInitialPosition(),
                            enemyTankMovements[i]->tankTranslate + enemyTanks[i]->GetInitialPosition());
            float PF = tank->GetTankRadius() + enemyTanks[i]->GetTankRadius() - distance;
            glm::vec3 P = PF * glm::normalize(diff);
            enemyTankMovements[i]->tankTranslate -= P;

            if (tankId == -1 && !helicopterPerspective)
            {
                PositionCameraBehindEntity(tankMovement);
            }
		}
	}
}

void m1::InitTema2::UpdateBasedOnTankBuildingCollision(Tank* tank, TankMovement* tankMovement, int tankId)
{
    for (int i = 0; i < building->GetBuildingPositions().size(); i++)
    {
        if (tank->CheckTankIndividualBuildingCollision(building, tankMovement->tankTranslate, i))
        {
			glm::vec3 diff = tank->GetInitialPosition() + tankMovement->tankTranslate - building->GetBuildingPositions()[i];
			float distance = glm::distance(tank->GetInitialPosition() + tankMovement->tankTranslate, building->GetBuildingPositions()[i]);
			float PF = tank->GetTankRadius() + building->GetBuildingRadiusPerType()[building->GetBuildingTypes()[i]] - distance;
			glm::vec3 P = PF * glm::normalize(diff);
			tankMovement->tankTranslate += P;

            if (tankId == -1 && !helicopterPerspective)
            {
                PositionCameraBehindEntity(tankMovement);
            }
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
		if (CheckBulletBuildingCollision(bullets[i]) || bullets[i]->GetBulletPosition().y <= 0)
		{
            Explosion* explosion = new Explosion(
                                    explosionObjects,
                                    bullets[i]->GetBulletPosition());
            explosions.push_back(explosion);
            firstExplisonFrames.push_back(true);

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
            landedShots++;
            if (enemyTanks[i]->GetDamage() > enemyTanks[i]->GetMaxDamage())
            {
				enemyTanks.erase(enemyTanks.begin() + i);
				enemyTankMovements.erase(enemyTankMovements.begin() + i);
				enemyTankPositions.erase(enemyTankPositions.begin() + i);
                kills++;
                sounds[FATALITY]->Kill();
                sounds[FATALITY]->Play();
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
            firstExplisonFrames.push_back(true);

			bullets.erase(bullets.begin() + i);
		}
	}
}

//float m1::InitTema2::ComputeEnemyTurretDirection(glm::vec3 enemyTankPosition, glm::vec3 playerTankPosition) {
//    const glm::vec3 vectorToPlayer = normalize(enemyTankPosition - playerTankPosition);
//    float newRotation = -DEGREES((vectorToPlayer.z > 0.0f) ? M_PI - asin(vectorToPlayer.x) : asin(vectorToPlayer.x));
//
//    return newRotation;
//}

//float m1::InitTema2::ComputeEnemyTurretDirection(glm::vec3 enemyTankPosition, glm::vec3 playerTankPosition) {
//    const glm::vec3 vectorToPlayer = normalize(playerTankPosition - enemyTankPosition);
//    float newRotation = atan2(vectorToPlayer.x, vectorToPlayer.z);
//    return newRotation; // Make sure this is in the correct format (radians or degrees) as expected by your engine
//}

float m1::InitTema2::ComputeEnemyTurretDirection(glm::vec3 enemyTankPosition, glm::vec3 playerTankPosition) {
    glm::vec3 vectorToPlayer = normalize(playerTankPosition - enemyTankPosition);
    float newRotation = atan2(vectorToPlayer.x, vectorToPlayer.z);
    return newRotation; // Ensure this is in radians or degrees as needed
}

//glm::vec3 m1::InitTema2::ComputeEnemyTurretDirection(glm::vec3 enemyTankPosition, glm::vec3 playerTankPosition) {
//    glm::vec3 direction = playerTankPosition - enemyTankPosition;
//    direction = glm::normalize(direction);
//
//    glm::vec3 turretRotation = glm::vec3(0, 0, 0);
//
//    // Compute rotation around Y-axis to face the player tank
//    float rotationAngle = atan2(direction.x, direction.z);
//    turretRotation.y = rotationAngle;
//
//    // Assuming no rotation around X and Z axes
//    turretRotation.x = 0;
//    turretRotation.z = 0;
//
//    return turretRotation;
//}


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

void InitTema2::LoopMusic()
{
    if (currentTime - lastTimeMusic > 80.0f)
    {
        sounds[MUSIC]->Kill();
		sounds[MUSIC]->Play();
		lastTimeMusic = currentTime;
	}
}

void InitTema2::LoopIdle() {
    if (currentTime - lastTimeEngineIdle > 8.0f)
    {
        if (!helicopterPerspective)
        {
            sounds[ENGINE_IDLE]->Kill();
            sounds[ENGINE_IDLE]->Play();
        }
        else
        {
            sounds[HELICOPTER]->Kill();
			sounds[HELICOPTER]->Play();
        }
        lastTimeEngineIdle = currentTime;
    }
}

void InitTema2::MenuSetup()
{
    RenderMenu();
    PlaceCameraForMenu();
}

void InitTema2::MenuActions()
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
    {
        int res = menu->CheckButtonPress(window->GetCursorPosition().x, window->GetCursorPosition().y);

        if (res == 1)
        {
            isMenu = false;
        }

        if (res == 2)
        {
            exit(0);
        }
    }
}

void InitTema2::PlaceCameraForMenu()
{
    camera->Set(glm::vec3(16, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

void m1::InitTema2::CloseIfDead()
{
    if (counterSinceDeath)
    {
        statsText->RenderDeathText(shaders);
        if (currentTime - counterSinceDeath > 5.0f)
        {
			exit(0);
        }
    }
}

void InitTema2::Update(float deltaTimeSeconds)
{
    if (isMenu)
    {
        LoopMusic();
        MenuSetup();
        MenuActions();
        return;
    }

    LoopMusic();
    LoopIdle();
    RenderGround();
    RenderBuildings();
    RenderSky();

    RandomizeEnemyTankMovement(deltaTimeSeconds);
    DetectInput();

    UpdateBasedOnTankBuildingCollision(tank, tankMovement, -1);
    for (int i = 0; i < enemyTanks.size(); i++)
    {
		UpdateBasedOnTankBuildingCollision(enemyTanks[i], enemyTankMovements[i], i);
	}
    UpdateBasedOnTankTankCollision(tank, tankMovement, -1);
    for (int i = 0; i < enemyTanks.size(); i++)
    {
        UpdateBasedOnTankTankCollision(enemyTanks[i], enemyTankMovements[i], i);
    }

    RenderHelicopterEntity();
    RenderTankEntity();
    RenderEnemyTankEntity();

    ShootOnLeftClick();
    MoveBulletsInLine();

    CheckAllBulletsBuildingCollisions();
    CheckAllBulletsTankCollisions();
    RenderExplosions();

    RenderStatsText();

    // Display main elements in the minimap
    UpdateMinimap();
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);
    glClear(GL_DEPTH_BUFFER_BIT);

    RenderGround(true);
    RenderBuildings(true);
    RenderHelicopterEntity(true);
    RenderTankEntity(true);
    RenderEnemyTankEntity(true);
    RenderExplosions(true);

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, window->GetResolution().x, window->GetResolution().y);

    CloseIfDead();

    currentTime += deltaTimeSeconds;
}

void InitTema2::UpdateMinimapProjectionAndView(glm::vec3 tankPosition) 
{
    float heightAboveTank = 100.0f;
    glm::vec3 cameraPosition = tankPosition + glm::vec3(0, heightAboveTank, 0);
    glm::vec3 lookAtTarget = tankPosition;
    glm::vec3 upDirection = glm::vec3(1, 0, 0);

    viewMatrixMiniMap = glm::lookAt(cameraPosition, lookAtTarget, upDirection);

    float orthoWidth = 20.0f;
    float orthoHeight = 20.0f;
    projectionMatrixMiniMap = glm::ortho(-orthoWidth / 2, orthoWidth / 2, -orthoHeight / 2, orthoHeight / 2, 0.01f, 100.f);
}

void InitTema2::UpdateMinimap() 
{
    glm::vec3 tankPosition = tankMovement->tankTranslate + tank->GetInitialPosition();
    glm::vec3 helicopterPosition = helicopterMovement->tankTranslate + helicopter->GetInitialPosition();
    helicopterPosition.y = 0;
    if (!helicopterPerspective)
    {
        UpdateMinimapProjectionAndView(tankPosition);
    }
    else
    {
        UpdateMinimapProjectionAndView(helicopterPosition);
    }
}

void InitTema2::FrameEnd()
{
    //DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


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
    // On key k damge my tank for debugging purposes
    if (key == GLFW_KEY_K)
    {
		tank->Damage();

        if (tank->GetDamage() > tank->GetMaxDamage())
        {
            if (!counterSinceDeath)
            {
                // Play the sound only once
                sounds.at(DIED)->Kill();
                sounds.at(DIED)->Play();
            }
            counterSinceDeath = currentTime;
		}
    }

    // On key h switch to helicopter perspective
    if (key == GLFW_KEY_H)
    {
		helicopterPerspective = !helicopterPerspective;
        if (helicopterPerspective)
        {
			sounds.at(ENGINE_IDLE)->Kill();
			sounds.at(ENGINE_WORKING)->Kill();
		}
	}
}


void InitTema2::OnKeyRelease(int key, int mods)
{
}


void InitTema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (!isMenu)
    {
        projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 100.f);
        PositionCameraThirdPerson(deltaX, deltaY);
    }
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