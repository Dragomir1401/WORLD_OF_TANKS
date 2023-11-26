#include "TankMovement.hpp"

m1::TankMovement::TankMovement(
	glm::vec3 tankTranslate,
	glm::vec3 tankRotate,
	glm::vec3 wheelTilt,
	int animationSkipper,
	int animationIndex,
	bool animationIncreaser,
	TankState tankState)
{
	this->tankTranslate = tankTranslate;
	this->tankRotate = tankRotate;
	this->wheelTilt = wheelTilt;
	this->animationSkipper = animationSkipper;
	this->animationIndex = animationIndex;
	this->animationIncreaser = animationIncreaser;
	this->tankState = tankState;
}

m1::TankMovement::~TankMovement()
{
}

void m1::TankMovement::MoveTowards(
	const glm::vec3& targetPosition, 
	float moveSpeed,
	float deltaTime, 
	glm::vec3 tankCurrentPosition)
{
	std::cout << "TankMovement::MoveTowards" << std::endl;

	// Direction from current position to target position
	glm::vec3 directionToTarget = glm::normalize(targetPosition - tankCurrentPosition);

	// Move the tank towards the target
	tankCurrentPosition += directionToTarget * moveSpeed * deltaTime;

	// Calculate the angle for the tank to rotate towards the target
	// atan2 parameters are swapped to accommodate for the tank facing along the X-axis when tankRotate.y is zero
	float targetAngle = atan2(directionToTarget.z, directionToTarget.x);

	// Adjust the target angle by 90 degrees (pi/2 radians) since the tank faces along the positive X-axis when tankRotate.y is zero
	targetAngle -= glm::half_pi<float>();

	// Set the tank's rotation to the target angle
	this->tankRotate.y = targetAngle;
}

void m1::TankMovement::MoveAway(
	const glm::vec3& targetPosition,
	float moveSpeed,
	float deltaTime,
	glm::vec3 tankCurrentPosition)
{
	std::cout << "TankMovement::MoveAway" << std::endl;
	glm::vec3 directionAwayFromTarget = glm::normalize(this->tankTranslate - targetPosition);
	this->tankTranslate += directionAwayFromTarget * moveSpeed * deltaTime; // Move away from the player

	// Rotate away from the player (opposite direction to where we want to go)
	float targetAngle = atan2(directionAwayFromTarget.x, directionAwayFromTarget.z);
	this->tankRotate.y = (float)(targetAngle + M_PI); // Add π radians to face the opposite direction
}

void m1::TankMovement::RotateRandomly(float deltaTime)
{
	std::cout << "TankMovement::RotateRandomly" << std::endl;
	static std::default_random_engine generator(std::random_device{}());
	std::uniform_real_distribution<float> randomRotation(-0.1f, 0.1f); // Adjust the range as needed for your game

	// Apply a small random rotation to the tank's current rotation
	this->tankRotate.y += randomRotation(generator) * deltaTime;
}


void m1::TankMovement::UpdateMovementState(
	glm::vec3 tankCurrentPosition,
	glm::vec3 playerPosition)
{
	float distanceToPlayer = glm::distance(tankCurrentPosition, playerPosition);

	if (distanceToPlayer > 20) {
		this->tankState = TankState::Chase;
	}
	else if (distanceToPlayer < 10) {
		this->tankState = TankState::Flee;
	}
	else {
		this->tankState = TankState::Idle;
	}
}