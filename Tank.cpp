#include "Tank.hpp"

m1::Tank::Tank(
    std::unordered_map<std::string, Mesh*> tankObjects,
    glm::vec3 initialPosition,
    bool isEnemy)
{
    this->tankObjects = tankObjects;
    this->initialPosition = initialPosition;
    this->isEnemy = isEnemy;
}

m1::Tank::~Tank()
{
}

glm::mat4 m1::Tank::RenderBody(
    std::unordered_map<std::string, Shader*> shaders,
    glm::vec3 tankTranslate,
    glm::vec3 tankRotate,
    bool minimap)
{
    glm::vec3 tankAdjustedTranslate = tankTranslate / tankScale;

    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, initialPosition);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(tankScale));
    modelMatrix = glm::translate(modelMatrix, tankAdjustedTranslate);
    modelMatrix = glm::rotate(modelMatrix, tankRotate.y, glm::vec3(0, 1, 0));

    if (!minimap)
    {
        m1::InitTema2::RenderMesh(tankObjects["body"], shaders["ShaderTank"], modelMatrix, damage);
    }
    else
    {
        m1::InitTema2::RenderMeshMinimap(tankObjects["body"], shaders["ShaderTank"], modelMatrix, damage);
    }

    return modelMatrix;
}

m1::TurretOrientation m1::Tank::RenderTurret(
    std::unordered_map<std::string, Shader*> shaders,
    glm::vec3 tankTranslate,
    glm::vec3 tankRotate,
    glm::vec3 mouseRotate,
    bool minimap)
{
    glm::vec3 tankAdjustedTranslate = tankTranslate / tankScale;
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, initialPosition);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(tankScale));
    modelMatrix = glm::translate(modelMatrix, tankAdjustedTranslate);
    if (!isEnemy)
    {
        modelMatrix = glm::rotate(modelMatrix, tankRotate.y, glm::vec3(0, 1, 0));
    }
    modelMatrix = glm::rotate(modelMatrix, -mouseRotate.y, glm::vec3(0, 1, 0));

    if (!minimap)
    {
        m1::InitTema2::RenderMesh(tankObjects["turet"], shaders["ShaderTank"], modelMatrix);
    }
    else
    {
        m1::InitTema2::RenderMeshMinimap(tankObjects["turet"], shaders["ShaderTank"], modelMatrix);
    }

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
    glm::vec3 mouseRotate,
    bool minimap)
{
    glm::vec3 tankAdjustedTranslate = tankTranslate / tankScale;
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, initialPosition);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(tankScale));
    modelMatrix = glm::translate(modelMatrix, tankAdjustedTranslate);
    if (!isEnemy)
    {
        modelMatrix = glm::rotate(modelMatrix, tankRotate.y, glm::vec3(0, 1, 0));
    }
    modelMatrix = glm::rotate(modelMatrix, -mouseRotate.y, glm::vec3(0, 1, 0));

    if (!minimap)
    {
        m1::InitTema2::RenderMesh(tankObjects["tun"], shaders["ShaderTank"], modelMatrix);
    }
    else
    {
        m1::InitTema2::RenderMeshMinimap(tankObjects["tun"], shaders["ShaderTank"], modelMatrix);
    }
}


void m1::Tank::RenderWheels(
    std::unordered_map<std::string, Shader*> shaders, 
    glm::vec3 tankTranslate, 
    glm::vec3 tankRotate, 
    glm::vec3 wheelTilt, 
    int animationIndex,
    bool minimap)
{
    glm::vec3 wheelAdjustedTranslate = tankTranslate / wheelScale;
    glm::vec3 wheelAdjustedRotate = tankRotate;
    int animationIndexReverse = 10 - animationIndex + 1;

    glm::mat4 intermediateModelMatrix1 = glm::mat4(1);
    glm::mat4 intermediateModelMatrix2 = glm::mat4(1);

    intermediateModelMatrix1 = glm::translate(intermediateModelMatrix1, initialPosition);
    intermediateModelMatrix1 = glm::scale(intermediateModelMatrix1, glm::vec3(wheelScale));
    intermediateModelMatrix1 = glm::translate(intermediateModelMatrix1, wheelAdjustedTranslate);
    intermediateModelMatrix1 = glm::rotate(intermediateModelMatrix1, tankRotate.y, glm::vec3(0, 1, 0));

    intermediateModelMatrix2 = glm::translate(intermediateModelMatrix2, initialPosition);
    intermediateModelMatrix2 = glm::scale(intermediateModelMatrix2, glm::vec3(wheelScale));
    intermediateModelMatrix2 = glm::rotate(intermediateModelMatrix2, RADIANS(180), glm::vec3(0, 1, 0));
    intermediateModelMatrix2 = glm::translate(intermediateModelMatrix2, -wheelAdjustedTranslate);
    intermediateModelMatrix2 = glm::rotate(intermediateModelMatrix2, tankRotate.y, glm::vec3(0, 1, 0));

    {
        // Rend the wheel 1 out of 8 at animationIndex
        std::string name = "wheel" + std::to_string(animationIndexReverse);
        glm::mat4 modelMatrix = intermediateModelMatrix1;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(3.4f, -0.39f, 0.35f));
        modelMatrix = glm::rotate(modelMatrix, wheelTilt.y, glm::vec3(0, 1, 0));
        if (!minimap)
        {
			m1::InitTema2::RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
		}
        else
        {
			m1::InitTema2::RenderMeshMinimap(tankObjects[name], shaders["ShaderTank"], modelMatrix);
		}
    }

    {
        // Rend the wheel 2 out of 8 at animationIndex
        std::string name = "wheel" + std::to_string(animationIndexReverse);
        glm::mat4 modelMatrix = intermediateModelMatrix1;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.9f, -0.42f, 0.35f));
        if (!minimap)
        {
            m1::InitTema2::RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
        }
        else
        {
            m1::InitTema2::RenderMeshMinimap(tankObjects[name], shaders["ShaderTank"], modelMatrix);
        }
    }

    {
        // Rend the wheel 3  out of 8 at animationIndex
        std::string name = "wheel" + std::to_string(animationIndexReverse);
        glm::mat4 modelMatrix = intermediateModelMatrix1;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.6f, -0.42f, 0.35f));
        if (!minimap)
        {
            m1::InitTema2::RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
        }
        else
        {
            m1::InitTema2::RenderMeshMinimap(tankObjects[name], shaders["ShaderTank"], modelMatrix);
        }
    }

    {
        // Rend the wheel 4 out of 8 at animationIndex
        std::string name = "wheel" + std::to_string(animationIndexReverse);
        glm::mat4 modelMatrix = intermediateModelMatrix1;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.7f, -0.42f, 0.35f));
        if (!minimap)
        {
            m1::InitTema2::RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
        }
        else
        {
            m1::InitTema2::RenderMeshMinimap(tankObjects[name], shaders["ShaderTank"], modelMatrix);
        }
    }

    {
        // Rend the wheel 5 out of 8 at animationIndex
        std::string name = "wheel" + std::to_string(animationIndex);
        glm::mat4 modelMatrix = intermediateModelMatrix2;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(3.8f, -0.39f, 0.35f));
        if (!minimap)
        {
            m1::InitTema2::RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
        }
        else
        {
            m1::InitTema2::RenderMeshMinimap(tankObjects[name], shaders["ShaderTank"], modelMatrix);
        }
    }

    {
        // Rend the wheel 6 out of 8 at animationIndex
        std::string name = "wheel" + std::to_string(animationIndex);
        glm::mat4 modelMatrix = intermediateModelMatrix2;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1.7f, -0.42f, 0.35f));
        if (!minimap)
        {
            m1::InitTema2::RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
        }
        else
        {
            m1::InitTema2::RenderMeshMinimap(tankObjects[name], shaders["ShaderTank"], modelMatrix);
        }
    }

    {
        // Rend the wheel 7 out of 8 at animationIndex
        std::string name = "wheel" + std::to_string(animationIndex);
        glm::mat4 modelMatrix = intermediateModelMatrix2;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.8f, -0.42f, 0.35f));
        if (!minimap)
        {
            m1::InitTema2::RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
        }
        else
        {
            m1::InitTema2::RenderMeshMinimap(tankObjects[name], shaders["ShaderTank"], modelMatrix);
        }
    }

    {
        // Rend the wheel 8 out of 8 at animationIndex
        std::string name = "wheel" + std::to_string(animationIndex);
        glm::mat4 modelMatrix = intermediateModelMatrix2;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.4f, -0.42f, 0.35f));
        modelMatrix = glm::rotate(modelMatrix, wheelTilt.y, glm::vec3(0, 1, 0));
        if (!minimap)
        {
            m1::InitTema2::RenderMesh(tankObjects[name], shaders["ShaderTank"], modelMatrix);
        }
        else
        {
            m1::InitTema2::RenderMeshMinimap(tankObjects[name], shaders["ShaderTank"], modelMatrix);
        }
    }
}


bool m1::Tank::CheckTankBuildingCollision(
    m1::Building* buildingBlock,
    glm::vec3 tankPosition)
{
    // For each building postion
    for (int i = 0; i < buildingBlock->GetBuildingPositions().size(); i++)
    {
        float buildingRadius = buildingBlock->GetBuildingRadiusPerType()[buildingBlock->GetBuildingTypes()[i]];
        float tankRadius = this->GetTankRadius();
        float distanceBetweenTankAndBuilding = glm::distance(tankPosition + this->initialPosition, buildingBlock->GetBuildingPositions()[i]);

        // If the distance between the tank and the building is less than the sum of their radiuses
        if (distanceBetweenTankAndBuilding < buildingRadius + tankRadius)
        {
            return true;
        }
    }
    return false;
}

bool m1::Tank::CheckTankIndividualBuildingCollision(
    m1::Building* buildingBlock,
    glm::vec3 tankPosition,
    int buildingIndex)
{
	float buildingRadius = buildingBlock->GetBuildingRadiusPerType()[buildingBlock->GetBuildingTypes()[buildingIndex]];
	float tankRadius = this->GetTankRadius();
	float distanceBetweenTankAndBuilding = glm::distance(tankPosition + this->initialPosition, buildingBlock->GetBuildingPositions()[buildingIndex]);

	// If the distance between the tank and the building is less than the sum of their radiuses
    if (distanceBetweenTankAndBuilding < buildingRadius + tankRadius)
    {
		return true;
	}

	return false;
}

bool m1::Tank::CheckTankMapBorderCollision(
    Sky* sky,
    glm::vec3 tankPosition)
{
    // If tank movement exceeds tank radius in any direction
    if (tankPosition.x + this->initialPosition.x > sky->GetSkyRadius() - tankRadius ||
        tankPosition.x + this->initialPosition.x < -sky->GetSkyRadius() + tankRadius ||
        tankPosition.z + this->initialPosition.z > sky->GetSkyRadius() - tankRadius ||
        tankPosition.z + this->initialPosition.z < -sky->GetSkyRadius() + tankRadius)
    {
		return true;
	}

    return false;
}

bool m1::Tank::CheckTankTankCollision(
    Tank* otherTank,
    glm::vec3 myTankPosition,
    glm::vec3 otherTankPosition)
{
    float myTankRadius = this->GetTankRadius();
    float otherTankRadius = otherTank->GetTankRadius();
    float distanceBetweenTanks = glm::distance(myTankPosition + this->initialPosition, otherTankPosition + otherTank->GetInitialPosition());

    // If the distance between the tank and the building is less than the sum of their radiuses
    if (distanceBetweenTanks < myTankRadius + otherTankRadius)
    {
		return true;
	}

    return false;
}

bool m1::Tank::CheckTankEnemyTanksCollision(
    std::vector<Tank*> enemyTanks,
    std::vector<TankMovement*> enemyTanksMovement,
    glm::vec3 tankPosition)
{
    // for every enemy tank check if the distance between the tanks is less than the sum of their radiuses
    for (int i = 0; i < enemyTanks.size(); i++)
	{
		if (this->CheckTankTankCollision(enemyTanks[i], tankPosition, enemyTanksMovement[i]->tankTranslate))
		{
			return true;
		}
	}

	return false;
}

