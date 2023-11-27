#pragma once

#include <string>
#include <iostream>
#include "Init.hpp"
namespace m1 {
    class Tank; // Forward declaration
}
namespace m1 {
    class Building; // Forward declaration
}

namespace m1
{
    class TankMovement
    {
    public:
        enum class TankState {
			Chase,
			Flee,
			Idle
		};
        TankMovement(
            glm::vec3 tankTranslate,
            glm::vec3 tankRotate,
            glm::vec3 wheelTilt,
            int animationSkipper,
            int animationIndex,
            bool animationIncreaser,
            TankState tankState);
        ~TankMovement();

        void MoveTowards(
            const glm::vec3& targetPosition, 
            float moveSpeed, 
            float deltaTime, 
            glm::vec3 tankCurrentPosition);

        void MoveAway(
            const glm::vec3& targetPosition,
            float moveSpeed,
            float deltaTime,
            glm::vec3 tankCurrentPosition);

        void IdleMove(
            float deltaTime, 
            Tank* tank,
            Building* building);

        void UpdateMovementState(
            glm::vec3 tankCurrentPosition,
            glm::vec3 playerPosition);


        glm::vec3 tankTranslate = glm::vec3(0, 0, 0);
        glm::vec3 tankRotate = glm::vec3(0, 0, 0);
        glm::vec3 wheelTilt = glm::vec3(0, 0, 0);
        int animationSkipper = 0;
        int animationIndex = 250;
        bool animationIncreaser = false;
        TankState tankState = TankState::Idle;
        float lastCommandTimer = 0;
        int randomNumber = rand() % 100;
    };
} // namespace m1