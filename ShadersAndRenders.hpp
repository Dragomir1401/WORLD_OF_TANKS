#pragma once

#include <vector>
#include "components/simple_scene.h"
#include "lab_camera.hpp"

namespace m1
{ 
	class ShadersAndRenders
	{
	public:

		ShadersAndRenders(
			std::unordered_map<std::string, Shader*> shaders,
			Camera* camera,
			glm::mat4 projectionMatrix);
		~ShadersAndRenders();
		void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);

		std::unordered_map<std::string, Shader*> shaders;
		Camera* camera;
		glm::mat4 projectionMatrix;
	};
} // namespace m1