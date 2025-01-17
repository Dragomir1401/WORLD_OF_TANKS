#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "components/simple_scene.h"
#include "lab_camera.hpp"
#include "Init.hpp"
#define NUM_PARCELS 8

namespace m1
{
	class Building
	{
	public:
		Building(std::unordered_map<std::string, Mesh*> buildingObjects);
		~Building();
		void RenderBuilding(std::unordered_map<std::string, Shader*> shaders, bool minimap = false);
		glm::vec3 FindRandomPositionOutsideOfBuilding();
		std::vector <glm::vec3> GetBuildingPositions();
		std::vector <int> GetBuildingTypes();
		std::vector <float> GetBuildingRadiusPerType();
		void DamageBuilding(int index);
	private:
		std::unordered_map<std::string, Mesh*> buildingObjects;
		float buildingBaseHeight = 0.02f;
		float buildingLength = 20.0f;
		std::vector <glm::vec3> buildingPositions;
		std::vector <float> damagePerPosition;
		std::vector <int> buildingTypes;
		std::vector <float> buildingRadiusPerType;
		int groundBoxNumbers = NUM_PARCELS;
		float groundLength = 20.0f;
		int numberOfBuildingTypes = 7;
		int resourcePerParcel[NUM_PARCELS * 2 + 1][NUM_PARCELS * 2 + 1];
		int skipIndex = 0;
		std::vector<glm::vec3> translations;
		bool firstIteration = true;
		int spawnRadius = 50;
	};
} // namespace m1