#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "components/simple_scene.h"
#include "lab_camera.hpp"

namespace m1
{
	class TurretOrientation {
	public:
		TurretOrientation();
		~TurretOrientation();
		glm::vec3 turretRelativeRotationWhenBulletWasShot;
		glm::mat4 turretWorldMatrixWhenBulletWasShot;
	};
} // namespace m1