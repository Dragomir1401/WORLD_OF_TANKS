#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "components/simple_scene.h"
#include "lab_camera.hpp"
#include "TurretOrientation.hpp"
#include "Init.hpp"
#include "TankMovement.hpp"
#include "Audio.hpp"

namespace m1
{
	class Helicopter
	{
	public:
		Helicopter(
			std::unordered_map<std::string, Mesh*> tankObjects,
			glm::vec3 initialPosition);
		~Helicopter();

		glm::vec3 GetInitialPosition() { return initialPosition; }
		float GetHelicopterRadius() { return helicopterRadius; }

		glm::mat4 RenderBody(
			std::unordered_map<std::string, Shader*> shaders,
			glm::vec3 helicopterTranslate,
			glm::vec3 helicopterRotate,
			bool minimap = false);

		void RenderBlade(
			std::unordered_map<std::string, Shader*> shaders,
			glm::vec3 helicopterTranslate,
			glm::vec3 helicopterRotate,
			int animationIndex,
			bool minimap = false);

		void RenderBackBlade(
			std::unordered_map<std::string, Shader*> shaders,
			glm::vec3 helicopterTranslate,
			glm::vec3 helicopterRotate,
			int animationIndex,
			bool minimap = false);

		float GetDamage() { return damage; }
		void Damage() { damage += 1.2f; }
		float GetMaxDamage() { return maxDamage; }

	private:
		std::unordered_map<std::string, Mesh*> helicopterObjects;
		glm::vec3 initialPosition;
		float helicopterRadius= 3.0f;
		float damage = 0;
		float maxDamage = 9.0f;
		glm::vec3 helicopterLastTranslate = glm::vec3(0, 0, 0);
	};
} // namespace m1