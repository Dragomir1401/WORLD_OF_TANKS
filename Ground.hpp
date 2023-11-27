#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "components/simple_scene.h"
#include "lab_camera.hpp"
#include "Init.hpp"

namespace m1
{
	class Ground
	{
	public:
		Ground(std::unordered_map<std::string, Mesh*> groundObjects);
		~Ground();
		void RenderGround(std::unordered_map<std::string, Shader*> shaders);
	private:
		std::unordered_map<std::string, Mesh*> groundObjects;
		float groundHeight = 0.02f;
		float groundLength = 20.0f;
		int groundBoxNumbers = 8;
	};
} // namespace m1