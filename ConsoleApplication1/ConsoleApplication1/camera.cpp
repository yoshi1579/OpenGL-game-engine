#include "camera.h"
#include <SDL2\SDL.h>
#include <math.h>  
#include "Player.h"

static float toRadians(float degree);

void Camera::CameraInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			// change pitch
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				pitch -= e.button.y * 0.1f;
			}
			// change yaw
			else if (e.button.button == SDL_BUTTON_RIGHT)
			{
				yaw -= e.button.x * 0.1f;
			}
		}
		else if (e.type == SDL_MOUSEWHEEL)
		{
			// change the distance between camera and player 
			distanceToPlayer -= e.wheel.y * 0.1f;;
		}
	}
}

void Camera::CameraMove(Player* player)
{
	//CameraInput();
	CalculateHorizontalDistance();
	CalculateVerticalDistance();
	float actualYaw = yaw ;

	// calculate pos x
	float posX = horitontalDistance * sin(actualYaw);

	// calculate pos z
	float posZ = horitontalDistance * cos(actualYaw) * (-1);
	glm::vec3 posVec = glm::vec3(posX, verticalDistance, posZ);

	pos = player->GetPosition() +  posVec;

	// calculate forward vec
	forward = CalculateForwardVec(player);
}

void Camera::CalculateHorizontalDistance()
{
	horitontalDistance = distanceToPlayer * cos((double)toRadians(pitch));
}

void Camera::CalculateVerticalDistance()
{
	verticalDistance = distanceToPlayer * sin((double)toRadians(pitch));
}

glm::vec3 Camera::CalculateForwardVec(Player * player)
{
	return glm::normalize(player->GetPosition() - pos);
}

void Camera::IncreasePitch(float amount)
{
	pitch -= amount * 0.01f;
}

void Camera::IncreaseYaw(float amount)
{
	yaw -= amount * 0.001f;
}

static float toRadians(float degree)
{
	return degree * PI / 180.0f;
}
