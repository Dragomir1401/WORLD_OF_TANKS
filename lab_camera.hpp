#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"


namespace m1
{
    class Camera
    {
    public:
        Camera()
        {
            position = glm::vec3(0, 2, 5);
            forward = glm::vec3(0, 0, -1);
            up = glm::vec3(0, 1, 0);
            right = glm::vec3(1, 0, 0);
            distanceToTarget = 2;
        }

        Camera(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
        {
            Set(position, center, up);
        }

        ~Camera()
        { }

        void Set(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
        {
            this->position = position;
            forward = glm::normalize(center - position);
            right = glm::cross(forward, up);
            this->up = glm::cross(right, forward);
        }

        glm::vec3 GetPosition() const
		{
			return position;
		}

        void SetPosition(const glm::vec3& position)
        {
            this->position = position;
        }

        void MoveForward(float distance)
        {
            glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
            position += dir * distance;
        }
        void MoveWithDirection(const glm::vec3& direction, float distance)
        {
			position += glm::normalize(direction) * distance;
		}

        void TranslateForward(float distance)
        {
            position += forward * distance;
        }

        void TranslateUpward(float distance)
        {
            position += up * distance;
        }

        void TranslateRight(float distance)
        {
            glm::vec3 rightGround = glm::normalize(glm::vec3(right.x, 0, right.z));
            position += rightGround * distance;
        }

        void RotateFirstPerson_OX(float angle)
        {
            glm::vec3 forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), angle, right) * glm::vec4(this->forward, 0)));
            this->forward = forward;
            this->up = glm::cross(right, forward);
        }

        void RotateFirstPerson_OY(float angle)
        {
            this->forward = glm::normalize(glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 0));
            this->right = glm::normalize(glm::rotate(glm::mat4(1.f), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 0));
            this->up = glm::normalize(glm::cross(right, forward));
        }

        void RotateThirdPerson_OY2(float angle, float plus)
        {
            TranslateForward(distanceToTarget);
            RotateFirstPerson_OY(plus);
            RotateFirstPerson_OY(angle);
            RotateFirstPerson_OY(-plus);
            TranslateForward(-distanceToTarget);
        }

        void RotateFirstPerson_OZ(float angle)
        {
            this->right = glm::normalize(glm::rotate(glm::mat4(1.f), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1));
            this->up = glm::cross(right, forward);
        }

        void RotateThirdPerson_OX(float angle)
        {
            TranslateForward(distanceToTarget);
            RotateFirstPerson_OX(angle);
            TranslateForward(-distanceToTarget);
        }

        void RotateThirdPerson_OY(float angle)
        {
            TranslateForward(distanceToTarget);
            RotateFirstPerson_OY(angle);
            TranslateForward(-distanceToTarget);
        }

        void RotateThirdPerson_OY(float angle, glm::vec3 pivotPoint)
        {
            // Translate the camera to the pivot point
            glm::vec3 offset = position - pivotPoint;

            // Rotate the offset
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0));
            offset = glm::vec3(rotation * glm::vec4(offset, 0.0f));

            // Set the camera's new position relative to the pivot point
            position = pivotPoint + offset;

            // Recalculate the forward vector
            forward = glm::normalize(pivotPoint - position);

            // Recalculate the right and up vectors to ensure they remain perpendicular to forward
            right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
            up = glm::normalize(glm::cross(right, forward));
        }

        void RotateThirdPerson_OZ(float angle)
        {
            TranslateForward(distanceToTarget);
            RotateFirstPerson_OZ(angle);
            TranslateForward(-distanceToTarget);
        }

        void RotateAroundTarget(float angleOX, float angleOY)
        {
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OX(angleOX);
			RotateFirstPerson_OY(angleOY);
			TranslateForward(-distanceToTarget);
		}

        glm::mat4 GetViewMatrix()
        {
            return glm::lookAt(position, position + forward, up);
        }

        glm::vec3 GetTargetPosition()
        {
            return position + forward * distanceToTarget;
        }

    public:
        float distanceToTarget;
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;
    };
}
