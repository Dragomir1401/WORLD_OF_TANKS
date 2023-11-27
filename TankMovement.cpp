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
	// Direction from current position to target position
	glm::vec3 directionToTarget = glm::normalize(targetPosition - tankCurrentPosition);

	// Move the tank towards the target
	this->tankTranslate += directionToTarget * moveSpeed * deltaTime;

	// Calculate the angle for the tank to rotate towards the target
	// atan2 parameters are swapped to accommodate for the tank facing along the X-axis when tankRotate.y is zero
	float targetAngle = atan2(directionToTarget.z, directionToTarget.x);

	// Adjust the target angle by 90 degrees (pi/2 radians) since the tank faces along the positive X-axis when tankRotate.y is zero
	targetAngle -= glm::half_pi<float>();

	// Set the tank's rotation to the target angle
	this->tankRotate.y = targetAngle;
}

void m1::TankMovement::MoveAway(const glm::vec3& targetPosition, float moveSpeed, float deltaTime, glm::vec3 tankCurrentPosition)
{
}

//void m1::TankMovement::MoveAway(
//	const glm::vec3& targetPosition,
//	float moveSpeed,
//	float deltaTime,
//	glm::vec3 tankCurrentPosition)
//{
	//// Calculate the vector from the tank to the player
	//glm::vec3 directionToPlayer = glm::normalize(targetPosition - tankCurrentPosition);

	//// Calculate the vector away from the player
	//glm::vec3 directionAwayFromPlayer = -directionToPlayer;

	//// Calculate the desired target rotation angle to face away from the player
	//float targetRotation = atan2(directionAwayFromPlayer.x, directionAwayFromPlayer.z);

	//// Normalize the current rotation
	//glm::vec3 tankCurrentRotation = fmod(this->tankRotate, 2 * M_PI);

	//// Calculate the shortest rotation direction towards the target rotation
	//float rotationDelta = targetRotation - tankCurrentRotation;
	//if (rotationDelta > M_PI) {
	//	rotationDelta -= 2 * M_PI;
	//}
	//else if (rotationDelta < -M_PI) {
	//	rotationDelta += 2 * M_PI;
	//}

	//// Determine the rotation amount per frame, this should be a small value for smooth rotation
	//float rotationAmount = moveSpeedSlow * deltaTime;
	//if (abs(rotationDelta) > rotationAmount) {
	//	tankCurrentRotation += (rotationDelta > 0 ? rotationAmount : -rotationAmount);
	//}
	//else {
	//	tankCurrentRotation = targetRotation;
	//}

	//// Convert the rotation to the forward direction
	//glm::vec3 forwardDir = glm::vec3(sin(tankCurrentRotation), 0, cos(tankCurrentRotation));

	//// Move the tank away from the player
	//tankCurrentPosition += forwardDir * moveSpeedSlow * deltaTime;

	//// Update the tank's translation and rotation to the new values
	//this->tankTranslate = tankCurrentPosition;
	//this->tankRotate.y = tankCurrentRotation;
//}

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

void m1::TankMovement::IdleMove(float currentTime, m1::Tank* tank, m1::Building* building)
{
	glm::vec3 forwardDir = glm::normalize(glm::vec3(cos(this->tankRotate.y), 0, -sin(this->tankRotate.y)));

	float moveSpeed = 0.007f;
	float moveSpeedFast = 0.030f;
	float moveSpeedSlow = 0.005f;
	this->wheelTilt.y = 0;

	if (randomNumber >= 0 && randomNumber < 50 && currentTime - lastCommandTimer < 3.0f)
	{
		this->animationSkipper += 2;
		this->tankTranslate += moveSpeed * forwardDir;
		if (tank->CheckTankBuildingCollision(building, this->tankTranslate))
		{
			std::cout << "Tank is colliding " << std::endl;
			this->animationSkipper -= 2;
			this->tankTranslate -= moveSpeed * forwardDir;
		}
	}
	else if (randomNumber >= 0 && randomNumber < 50)
	{
		lastCommandTimer = currentTime;
		randomNumber = rand() % 100;
	}

	if (randomNumber >= 50 && randomNumber < 60 && currentTime - lastCommandTimer < 3.0f)
	{
		this->animationSkipper += 8;
		this->tankTranslate += moveSpeedFast * forwardDir;
		if (tank->CheckTankBuildingCollision(building, this->tankTranslate))
		{
			std::cout << "Tank is colliding " << std::endl;
			this->animationSkipper -= 8;
			this->tankTranslate -= moveSpeedFast * forwardDir;
		}
	}
	else if (randomNumber >= 50 && randomNumber < 60)
	{
		lastCommandTimer = currentTime;
		randomNumber = rand() % 100;
	}

	if (randomNumber >= 60 && randomNumber < 70 && currentTime - lastCommandTimer < 3.0f)
	{
		this->tankTranslate += moveSpeedSlow * -forwardDir;
		this->animationSkipper++;
		this->animationIncreaser = true;
		if (tank->CheckTankBuildingCollision(building, this->tankTranslate))
		{
			std::cout << "Tank is colliding " << std::endl;
			this->tankTranslate -= moveSpeedSlow * -forwardDir;
			this->animationSkipper--;
			this->animationIncreaser = false;
		}
	}
	else if (randomNumber >= 60 && randomNumber < 70)
	{
		lastCommandTimer = currentTime;
		randomNumber = rand() % 100;
	}

	if (randomNumber >= 70 && randomNumber < 85 && currentTime - lastCommandTimer < 3.0f)
	{
		this->tankRotate.y += moveSpeedSlow;
		this->wheelTilt.y = 0.3f;
		this->animationSkipper++;
	}
	else if (randomNumber >= 70 && randomNumber < 85)
	{
		lastCommandTimer = currentTime;
		randomNumber = rand() % 100;
	}

	if (randomNumber >= 85 && randomNumber < 100 && currentTime - lastCommandTimer < 3.0f)
	{
		this->tankRotate.y -= moveSpeedSlow;
		this->wheelTilt.y = -0.3f;
		this->animationSkipper++;
	}
	else if (randomNumber >= 85 && randomNumber < 100)
	{
		lastCommandTimer = currentTime;
		randomNumber = rand() % 100;
	}
}

