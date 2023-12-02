#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "components/simple_scene.h"
#include "lab_camera.hpp"
#include "Init.hpp"

namespace m1
{
	class Sky
	{
	public:
		Sky(std::unordered_map<std::string, Mesh*> skyObjects);
		~Sky();
		void RenderSky(std::unordered_map<std::string, Shader*> shaders);
		float GetSkyRadius()
		{
			return skyRadius;
		}
	private:
		std::unordered_map<std::string, Mesh*> skyObjects;
		float skyScale = 130.0f;
		float skyRadius = 130.0f * 1.314f;
	};
} // namespace m1