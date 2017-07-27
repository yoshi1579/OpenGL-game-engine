#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Player;
const float PI = 3.1415926535f;

struct Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar, float distance)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, zNear, zFar);
		this->right = glm::normalize(glm::cross(up, forward));
		distanceToPlayer = distance;
	}

	void CameraInput();
	void CameraMove(Player* player);
	void CalculateHorizontalDistance();
	void CalculateVerticalDistance();
	glm::vec3 CalculateForwardVec(Player* player);

	void IncreasePitch(float amount);
	void IncreaseYaw(float amount);

	inline glm::vec3 GetPos() { return pos; }

	inline glm::mat4 GetViewMatrix() {
		return glm::lookAt(pos, pos + forward, up);
	}

	inline glm::mat4 GetProjectionMatrix() 
	{ 
		return projection; 
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	inline void MoveForward(float amt)
	{
		pos += forward * amt;
	}

	inline void MoveBackword(float amt)
	{
		pos -= forward * amt;
	}

	inline void MoveRight(float amt)
	{
		pos -= glm::cross(up, forward) * amt;
	}

	inline void MoveLeft(float amt)
	{
		pos += glm::cross(up, forward) * amt;
	}

	inline void Pitch(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(up, forward));

		forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
		up = glm::normalize(glm::cross(forward, right));
	}

	inline void RotateY(float angle)
	{
		static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

		glm::mat4 rotation = glm::rotate(angle, UP);

		forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
		up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	}

protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;
	float pitch = 20;
	float yaw = 0;
	float distanceToPlayer = 50;
	float horitontalDistance = 0;
	float verticalDistance = 0;
};

#endif