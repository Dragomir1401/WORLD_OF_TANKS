#include "Bullet.hpp"

Bullet::Bullet(glm::vec3 position,
	std::unordered_map<std::string,
	Mesh*> meshes,
	int animationIndex,
	glm::vec3 bulletRotation,
	glm::mat4 tankWorldMatrixWhenBulletWasShot,
	glm::vec3 mouseRotationWhenBulletWasShot,
	glm::vec3 turretRelativeRotationWhenBulletWasShot,
	float bulletScale)
{
	this->position = position;
	this->meshes = meshes;
	this->animationIndex = animationIndex;
	this->bulletScale = bulletScale;
	this->tankRotation = bulletRotation;
	this->tankWorldMatrixWhenBulletWasShot = tankWorldMatrixWhenBulletWasShot;
	this->mouseRotationWhenBulletWasShot = mouseRotationWhenBulletWasShot;
	this->turretRelativeRotationWhenBulletWasShot = turretRelativeRotationWhenBulletWasShot;

	glm::vec4 bulletWorldPosition = tankWorldMatrixWhenBulletWasShot * glm::vec4(relativePositionToTankOrigin, 1.0f);
	this->position = glm::vec3(bulletWorldPosition);
}

Bullet::~Bullet()
{
}