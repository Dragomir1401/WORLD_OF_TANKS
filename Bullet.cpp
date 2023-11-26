#include "Bullet.hpp"

m1::Bullet::Bullet(
	glm::vec3 position,
	std::unordered_map<std::string,
	Mesh*> meshes,
	int animationIndex,
	glm::vec3 bulletRotation,
	glm::mat4 tankWorldMatrixWhenBulletWasShot,
	glm::vec3 mouseRotationWhenBulletWasShot,
	glm::vec3 turretRelativeRotationWhenBulletWasShot,
	glm::mat4 turretWorldMatrixWhenBulletWasShot,
	float shootedTime,
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
	this->turretWorldMatrixWhenBulletWasShot = turretWorldMatrixWhenBulletWasShot;
	this->shootedTime = shootedTime;

	glm::vec4 bulletWorldPosition = turretWorldMatrixWhenBulletWasShot * glm::vec4(relativePositionToTankOrigin, 1.0f);
	this->position = glm::vec3(bulletWorldPosition);
}

m1::Bullet::~Bullet()
{
}

bool m1::Bullet::RendBullet(float currentTime, std::unordered_map<std::string, Shader*> shaders)
{
	if (this->timerExpired == true)
	{
		return false;
	}

	this->animationIndex++;
	if (this->animationIndex > 60)
	{
		this->animationIndex = 21;
	}

	glm::vec3 direction = glm::vec3(cos(this->turretRelativeRotationWhenBulletWasShot.y),
		0,
		-sin(this->turretRelativeRotationWhenBulletWasShot.y));

	this->position += direction * bulletSpeed;

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, this->position);
	modelMatrix = glm::rotate(modelMatrix, RADIANS(270), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, this->turretRelativeRotationWhenBulletWasShot.y, glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(this->bulletScale));

	m1::InitTema2::RenderMesh(this->meshes["projectile" + std::to_string(this->animationIndex)], shaders["ShaderTank"], modelMatrix);

	if (currentTime - this->shootedTime > 7.0f)
	{
		this->timerExpired = true;
	}

	return true;
}
