#include "Building.hpp"

m1::Building::Building(std::unordered_map<std::string, Mesh*> buildingObjects)
{
	this->buildingObjects = buildingObjects;
    for (int i = 0; i < NUM_PARCELS * 2; ++i)
    {
        for (int j = 0; j < NUM_PARCELS * 2; ++j)
        {
			resourcePerParcel[i][j] = (rand() % (numberOfBuildingTypes - 1)) + 1;
		}
	}
}

m1::Building::~Building()
{
}

void m1::Building::RenderBuilding(std::unordered_map<std::string, Shader*> shaders)
{
    glm::mat4 modelMatrix;
    std::vector<glm::vec3> translations;

    for (int i = -groundBoxNumbers; i <= groundBoxNumbers; ++i)
    {
        for (int j = -groundBoxNumbers; j <= groundBoxNumbers; ++j) 
        {
            translations.push_back(glm::vec3(i * groundLength, 0, j * groundLength));
        }
    }

    int trranslationIndex = 0;
    for (int i = 0; i < NUM_PARCELS * 2; ++i)
    {
        for (int j = 0; j < NUM_PARCELS * 2; ++j)
        {
            if (translations[trranslationIndex].x == 0 && translations[trranslationIndex].z == 0)
            {
				trranslationIndex++;
				continue;
			}

            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, translations[trranslationIndex]);
            std::string name = "cottage" + std::to_string(resourcePerParcel[i][j]);
            if (resourcePerParcel[i][j] == 6)
            {
                name = "tower";
            }
			else if (resourcePerParcel[i][j] == 7)
            {
                name = "church";
            }
            m1::InitTema2::RenderMesh(buildingObjects[name], shaders["ShaderTank"], modelMatrix);
            trranslationIndex++;
        }
    }
}
