#pragma once

#include <vector>

#include "components/simple_scene.h"


namespace m1
{
    class InitTema2 : public gfxc::SimpleScene
    {
     public:
        InitTema2();
        ~InitTema2();

        void Init() override;

     private:
        void CreateTankEntity();
        void RenderTexturedMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1 = NULL, Texture2D* texture2 = NULL);
        void ParseTextures();
        void RenderMeshTexture(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1 = NULL, Texture2D* texture2 = NULL);
        void RenderTankEntity();
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void UpdateAnimationTrackers(bool& animationIncreaser);
        void DetectInput();
        glm::vec3 ComputeRotationBasedOnMouse();
        

        float elapsedTime;
        std::unordered_map<std::string, Mesh*> tankObjects;
        std::unordered_map<std::string, Texture2D*> textures;
        int animationIndex = 250;
        glm::vec3 lastWheelPosition;
        glm::vec3 tankTranslate = glm::vec3(0, 0, 0);
        glm::vec3 tankRotate = glm::vec3(0, 0, 0);
        glm::vec3 wheelTilt = glm::vec3(0, 0, 0);
        int animationSkipper = 0;
        glm::vec3 bodyTankPosition = glm::vec3(0, 0, 0);
        glm::vec3 bodyTankCenter = glm::vec3(0, 0, 0);
        glm::vec3 bodyMM = glm::vec3(0, 0, 0);
    };
}   // namespace m1
