#include "Building.hpp"

m1::Building::Building(std::unordered_map<std::string, Mesh*> buildingObjects)
{
	this->buildingObjects = buildingObjects;
    for (int i = 0; i < NUM_PARCELS * 2; ++i)
    {
        for (int j = 0; j < NUM_PARCELS * 2; ++j)
        {
			resourcePerParcel[i][j] = (rand() % numberOfBuildingTypes) + 1;

            if (skipIndex > 1)
            {
                resourcePerParcel[i][j] = -1;
                skipIndex = 0;
            }

            skipIndex++;
		}
	}


    for (int i = -groundBoxNumbers; i <= groundBoxNumbers; ++i)
    {
        for (int j = -groundBoxNumbers; j <= groundBoxNumbers; ++j) 
        {
            translations.push_back(glm::vec3(i * groundLength, 0, j * groundLength));
        }
    }

    buildingRadiusPerType.push_back(0.0f);
	buildingRadiusPerType.push_back(6.3f);
    buildingRadiusPerType.push_back(3.6f);
    buildingRadiusPerType.push_back(5.3f);
    buildingRadiusPerType.push_back(6.3f);
    buildingRadiusPerType.push_back(6.1f);
    buildingRadiusPerType.push_back(2.0f);
    buildingRadiusPerType.push_back(5.0f);
}

m1::Building::~Building()
{
}

void m1::Building::RenderBuilding(std::unordered_map<std::string, Shader*> shaders)
{
    int translationIndex = 0;
    int realIndex = 0;
    for (int i = 0; i < NUM_PARCELS * 2; ++i)
    {
        for (int j = 0; j < NUM_PARCELS * 2; ++j)
        {
            if (translations[translationIndex].x == 0 && translations[translationIndex].z == 0)
            {
				translationIndex++;
				continue;
			}

            std::string name = "cottage" + std::to_string(resourcePerParcel[i][j]);
            if (resourcePerParcel[i][j] == 6)
            {
                name = "tower";
            }
			else if (resourcePerParcel[i][j] == 7)
            {
                name = "church";
            }
            else if (resourcePerParcel[i][j] == -1)
            {
                translationIndex++;
                continue;
            }

            glm::mat4 modelMatrix;
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, translations[translationIndex]);

            if (firstIteration)
            {
                buildingPositions.push_back(translations[translationIndex]);
                damagePerPosition.push_back(0);
                buildingTypes.push_back(resourcePerParcel[i][j]);
            }

            m1::InitTema2::RenderMesh(buildingObjects[name], shaders["ShaderTank"], modelMatrix, damagePerPosition[realIndex]);
            translationIndex++;
            realIndex++;
        }
    }
    firstIteration = false;
}

glm::vec3 m1::Building::FindRandomPositionOutsideOfBuilding()
{
    glm::vec3 position;
    position.x = (float)(rand() % 15);
    position.y = 0;
    position.z = (float)(rand() % 15);

    for (int i = 0; i < buildingPositions.size(); i++)
    {
		if (position.x >= buildingPositions[i].x - buildingRadiusPerType[buildingTypes[i]] &&
			position.x <= buildingPositions[i].x + buildingRadiusPerType[buildingTypes[i]] &&
			position.z >= buildingPositions[i].z - buildingRadiusPerType[buildingTypes[i]] &&
			position.z <= buildingPositions[i].z + buildingRadiusPerType[buildingTypes[i]])
		{
            if (position.x <= buildingPositions[i].x)
			{
                position.x -= buildingRadiusPerType[buildingTypes[i]] - 1;
			}
			else
			{
                position.x += buildingRadiusPerType[buildingTypes[i]] + 1;
			}

            if (position.z <= buildingPositions[i].z)
			{
                position.z -= buildingRadiusPerType[buildingTypes[i]] - 1;
			}
            else
            {
                position.z += buildingRadiusPerType[buildingTypes[i]] + 1;
            }

            break;
		}
    }

    return position;
}

std::vector <glm::vec3> m1::Building::GetBuildingPositions()
{
	return buildingPositions;
}

std::vector <int> m1::Building::GetBuildingTypes()
{
	return buildingTypes;
}

std::vector <float> m1::Building::GetBuildingRadiusPerType()
{
	return buildingRadiusPerType;
}

void m1::Building::DamageBuilding(int index)
{
	damagePerPosition[index] += 1.5f;
}
