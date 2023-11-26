#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "components/simple_scene.h"
#include "lab_camera.hpp"
#include "Init.hpp"

namespace m1
{
	class Bullet
	{
	public:
		Bullet(
			glm::vec3 position,
			std::unordered_map<std::string, Mesh*> meshes,
			int animationIndex,
			glm::vec3 bulletRotation,
			glm::mat4 tankWorldMatrixWhenBulletWasShot,
			glm::vec3 mouseRotationWhenBulletWasShot,
			glm::vec3 turretRelativeRotationWhenBulletWasShot,
			glm::mat4 turretWorldMatrixWhenBulletWasShot,
			float shootedTime,
			float bulletScale = 0.3f);
		~Bullet();
		bool RendBullet(float currentTime, std::unordered_map<std::string, Shader*> shaders);
	private:
		glm::vec3 position;
		std::unordered_map<std::string, Mesh*> meshes;
		int animationIndex = 1;
		float bulletScale = 0.25f;
		glm::vec3 tankRotation = glm::vec3(0, 0, 0);
		glm::vec3 relativePositionToTankOrigin = glm::vec3(7.75f, 3.2f, 0);
		float tankScale = 0.35f;
		glm::mat4 tankWorldMatrixWhenBulletWasShot;
		glm::vec3 mouseRotationWhenBulletWasShot = glm::vec3(0, 0, 0);
		glm::vec3 turretRelativeRotationWhenBulletWasShot = glm::vec3(0, 0, 0);
		glm::mat4 turretWorldMatrixWhenBulletWasShot;
		bool timerExpired = false;
		float shootedTime = 0;
		float bulletSpeed = 0.25f;
	};
} // namespace m1