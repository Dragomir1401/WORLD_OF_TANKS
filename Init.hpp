#pragma once

#include <vector>
#include <random>
#include "components/simple_scene.h"
#include "lab_camera.hpp"
#include "Bullet.hpp"
#include "Tank.hpp"
#include "TurretOrientation.hpp"
#include "Ground.hpp"
#include "TankMovement.hpp"
#include "Building.hpp"
#include "Sky.hpp"
#include "Explosion.hpp"
#include "Audio.hpp"
#include "Menu.hpp"
#include "components/text_renderer.h"
#include "StatsText.hpp"
#include "Helicopter.hpp"
#define NUM_ENEMY_TANKS 5

namespace m1 {
    class Bullet; // Forward declaration
}
namespace m1 {
    class Tank; // Forward declaration
}
namespace m1 {
    class TurretOrientation; // Forward declaration
}
namespace m1 {
    class Ground; // Forward declaration
}
namespace m1 {
	class TankMovement; // Forward declaration
}
namespace m1 {
	class Building; // Forward declaration
}
namespace m1 {
	class Sky; // Forward declaration
}
namespace m1 {
	class Explosion; // Forward declaration
}
namespace m1 {
	class Menu; // Forward declaration
}
namespace m1 {
	class StatsText; // Forward declaration
}
namespace m1 {
	class Helicopter; // Forward declaration
}

struct TankPosition
{
    glm::mat4 tankWorldMatrix = glm::mat4(1);
    glm::vec3 tankCurrentPosition = glm::vec3(0, 0, 0);
    m1::TurretOrientation turretOrientation;
};

struct ViewportArea
{
    ViewportArea() : x(0), y(0), width(1), height(1) {}
    ViewportArea(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}
    int x;
    int y;
    int width;
    int height;
};

namespace m1
{
    class InitTema2 : public gfxc::SimpleScene
    {
     public:
        // Make enum for sound identification
        enum Sound
        {
            MUSIC,
			ENGINE_IDLE,
            ENGINE_WORKING,
            SHOOT,
            EXPLOSION_CLOSE,
            EXPLOSION_MID,
            EXPLOSION_FAR,
            FATALITY,
            DIED,
            HELICOPTER
		};
        InitTema2();
        ~InitTema2();

        void Init() override;
        static void RenderMesh(
            Mesh* mesh, 
            Shader* shader, 
            const glm::mat4& modelMatrix,
            float damageGrade = 0.0f);
        void RenderTexturedMesh(
            Mesh* mesh,
            Shader* shader,
            const glm::mat4& modelMatrix,
            Texture2D* texture1,
            Texture2D* texture2);
        static void RenderMeshMinimap(
            Mesh* mesh,
            Shader* shader,
            const glm::mat4& modelMatrix,
            float damageGrade = 0.0f
            );
        static glm::mat4 projectionMatrix;
        static glm::mat4 projectionMatrixMiniMap;
        static glm::mat4 viewMatrix;
        static glm::mat4 viewMatrixMiniMap;
        static Camera* camera;

     private:
        void CreateTankEntity(
            std::string sourceObjDirTank,
            bool isEnemy);
        void CreateHelicopterEntity();
        void CreateEmemyTankEntity();
        void CreateProjectileEntity();
        void CreateGroundEntity();
        void CreateSkyEntity();
        void CreateBuildingEntity();
        void CreateExplosionEntity();
        void CreateMenuEntity(glm::ivec2 resolution);
        void CreateStatsTextEntity(glm::ivec2 resolution);
        void LoadSounds();

        void RenderTankEntity(bool minimap = false);
        void RenderHelicopterEntity(bool minimap = false);
        void RenderEnemyTankEntity(bool minimap = false);
        void RenderExplosions(bool minimap = false);
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
        void UpdateAnimationTrackers(
            bool& animationIncreaser,
            m1::TankMovement* tankMovement);
        void DetectInput();
        void RandomizeEnemyTankMovement(
            float deltaTime);
        glm::vec3 ComputeRotationBasedOnMouse();
        void PositionCameraThirdPerson(
            int deltaX, 
            int deltaY);
        void ShootOnLeftClick();
        void MoveBulletsInLine();
        void RenderGround(bool minimap = false);
        void RenderSky();
        void RenderBuildings(bool minimap = false);
        void RenderMenu();
        void RenderStatsText();
        void UpdateBasedOnTankTankCollision(
            Tank* tank, 
            TankMovement* tankMovement, 
            int tankId);
        void UpdateBasedOnTankBuildingCollision(
            Tank* tank, 
            TankMovement* tankMovement,
            int tankId);
        bool CheckBulletBuildingCollision(
            m1::Bullet* bullet);
        void CheckAllBulletsBuildingCollisions();
        bool CheckBulletTankCollision(
            m1::Bullet* bullet);
        void CheckAllBulletsTankCollisions();
        float ComputeEnemyTurretDirection(
            glm::vec3 enemyTankPosition,
            glm::vec3 playerTankPosition);
        void PositionCameraBehindEntity(TankMovement* movement);
        void InitTema2::UpdateMinimapProjectionAndView(
            glm::vec3 tankPosition);
        void UpdateMinimap();
        void LoopMusic();
        void LoopIdle();
        void MenuSetup();
        void MenuActions();
        void PlaceCameraForMenu();
        void CloseIfDead();
        
        float elapsedTime = 0;
        m1::Tank* tank = nullptr;
        m1::Helicopter* helicopter = nullptr;
        m1::TankMovement* tankMovement;
        m1::TankMovement* helicopterMovement;
        TankPosition tankPosition;
        TankPosition helicopterPosition;
        m1::Ground* ground = nullptr;
        m1::Sky* sky = nullptr;
        m1::Building* building = nullptr;
        m1::Menu* menu = nullptr;
        m1::StatsText* statsText = nullptr;
        std::vector<m1::Tank*> enemyTanks;
        std::vector<m1::TankMovement*> enemyTankMovements;
        std::vector<TankPosition> enemyTankPositions;
        std::vector<m1::Bullet*> bullets;
        std::vector<m1::Explosion*> explosions;
        std::unordered_map<std::string, Mesh*> tankObjects;
        std::unordered_map<std::string, Mesh*> helicopterObjects;
        std::unordered_map<std::string, Mesh*> enemyTankObjects;
        std::unordered_map<std::string, Mesh*> projectileObjects;
        std::unordered_map<std::string, Mesh*> groundObjects;
        std::unordered_map<std::string, Mesh*> buildingObjects;
        std::unordered_map<std::string, Mesh*> skyObjects;
        std::unordered_map<std::string, Mesh*> explosionObjects;
        std::unordered_map<std::string, Mesh*> menuObjects;
        glm::vec3 initialCameraPosition = glm::vec3(0, 0, 0);
        glm::vec3 lastTuretRotation = glm::vec3(0, 0, 0);
        ViewportArea miniViewportArea;

        float cameraSpeed = 200.0f;
        float currentTime = 0;
        float lastTimeShot = 0;
        float fov = 60;
        int numberOfEnemyTanks = NUM_ENEMY_TANKS;

        float right;
        float left;
        float bottom;
        float top;

        std::vector<Audio*> sounds;
        float lastTimeMusic = 0;
        float lastTimeEngineIdle = 0;
        float lastTimeEngineWorking = 0;
        std::vector<bool> firstExplisonFrames = { true };

        bool isMenu = true;
        gfxc::TextRenderer* textRenderer;
        gfxc::TextRenderer* statsRenderer;
        int kills = 0;
        int landedShots = 0;

        float counterSinceDeath = 0;
        bool helicopterPerspective = false;
        float helicopterHeightOfFlying = 5;
    };
} // namespace m1
