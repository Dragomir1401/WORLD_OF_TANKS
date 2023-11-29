#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "components/simple_scene.h"
#include "lab_camera.hpp"
#include "TurretOrientation.hpp"
#include "Init.hpp"
#include "TankMovement.hpp"

namespace m1 {
	class Tank; // Forward declaration
}
namespace m1 {
	class Building; // Forward declaration
}
namespace m1 {
	class TankMovement; // Forward declaration
}

namespace m1
{
	class Tank
	{
	public:
		Tank(
			std::unordered_map<std::string, Mesh*> tankObjects,
			glm::vec3 initialPosition);
		~Tank();

		glm::vec3 GetInitialPosition() { return initialPosition; }
		float GetTankRadius() { return tankRadius; }

		glm::mat4 RenderBody(
			std::unordered_map<std::string, Shader*> shaders,
			glm::vec3 tankTranslate,
			glm::vec3 tankRotate);

		TurretOrientation RenderTurret(
			std::unordered_map<std::string, Shader*> shaders,
			glm::vec3 tankTranslate,
			glm::vec3 tankRotate,
			glm::vec3 mouseRotate);

		void RenderTun(
			std::unordered_map<std::string,
			Shader*> shaders,
			glm::vec3 tankTranslate,
			glm::vec3 tankRotate,
			glm::vec3 mouseRotate);

		void RenderWheels(
			std::unordered_map<std::string, Shader*> shaders,
			glm::vec3 tankTranslate,
			glm::vec3 tankRotate,
			glm::vec3 wheelTilt,
			int animationIndex);

		bool CheckTankBuildingCollision(
			Building* buildingBlock,
			glm::vec3 tankPosition);

		bool CheckTankTankCollision(
			Tank* otherTank,
			glm::vec3 tankPosition,
			glm::vec3 otherTankPosition);

		bool CheckTankEnemyTanksCollision(
			std::vector<Tank*> enemyTanks,
			std::vector<TankMovement*> enemyTanksMovement,
			glm::vec3 tankPosition);

		float GetDamage() { return damage; }
		void Damage() { damage += 1.2f; }
		float GetMaxDamage() { return maxDamage; }

	private:
		std::unordered_map<std::string, Mesh*> tankObjects;
		float tankScale = 0.35f;
		float wheelScale = 0.385f;
		glm::vec3 initialPosition;
		float tankRadius = 5.0f * 0.35f;
		float damage = 0;
		float maxDamage = 5.0f;
	};
} // namespace m1