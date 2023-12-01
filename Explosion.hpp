#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "components/simple_scene.h"
#include "lab_camera.hpp"
#include "Init.hpp"

namespace m1
{
	class Explosion
	{
	public:
		Explosion(
			std::unordered_map<std::string, Mesh*> meshes,
			glm::vec3 position
		);
		~Explosion();

		bool RendExplosion(
			std::unordered_map<std::string, Shader*> shaders,
			bool minimap = false);
		int GetAnimationIndex();

	private:
		glm::vec3 position;
		std::unordered_map<std::string, Mesh*> meshes;
		int animationIndex = 1;
	};
}