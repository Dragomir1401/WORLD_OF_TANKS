#pragma once

#include <vector>

#include "components/simple_scene.h"
#include "lab_camera.hpp"
#include "Bullet.hpp"


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
        void ParseTextures();
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
        void PositionCameraThirdPerson(int deltaX, int deltaY);
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
        void ShootOnLeftClick();
        void MoveBulletsInLine();
        

        float elapsedTime;
        std::unordered_map<std::string, Mesh*> tankObjects;
        std::unordered_map<std::string, Mesh*> projectileObjects;
        std::unordered_map<std::string, Texture2D*> textures;
        std::vector<Bullet*> bullets;
        int animationIndex = 250;
        glm::vec3 lastWheelPosition;
        glm::vec3 tankTranslate = glm::vec3(0, 0, 0);
        glm::vec3 tankRotate = glm::vec3(0, 0, 0);
        glm::vec3 turretRotate = glm::vec3(0, 0, 0);
        glm::vec3 turretRelativeRotate = glm::vec3(0, 0, 0);
        glm::vec3 wheelTilt = glm::vec3(0, 0, 0);
        int animationSkipper = 0;
        glm::mat4 projectionMatrix;
        glm::vec3 initialCameraPosition = glm::vec3(0, 0, 0);
        glm::vec3 lastTuretRotation = glm::vec3(0, 0, 0);
        glm::vec3 tankCurrentPosition = glm::vec3(0, 0, 0);
        glm::mat4 tankWorldMatrix;
        Camera* camera;
        float right;
        float left;
        float bottom;
        float top;
        float fov;
        float cameraSpeed = 200.0f;
        float currentTime = 0;
        float lastTimeShot = 0;
    };
}   // namespace m1
