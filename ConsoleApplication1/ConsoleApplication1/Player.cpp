#include "Player.h"
#include <SDL2\SDL.h>
#include <math.h>  

static float toRadians(float degree);

Player::Player()
{
}

void Player::move(double fps, Terrain* terrain)
{
	increseRotation(glm::vec3(0, currentTurnSpeed * fps, 0));
	float distance = currentSpeed * fps;
	upwardSpeed += GRAVITY * 1/fps;
	increasePosition(glm::vec3(distance* sin((double)(GetRotation().y)), upwardSpeed * 1/fps, distance* cos((double)GetRotation().y)));
	
	float terrainHeight = terrain->GetTerrainHeight(transforms.front().GetPos().x, transforms.front().GetPos().z);
	if (GetPosition().y <= terrainHeight + 5)
	{
		SetPositionY(terrainHeight + 5);
		upwardSpeed = 0;
		isInAir = false;
	}

}

void Player::SetCurrentTurnSpeed(float newTurnSpeed)
{
	currentTurnSpeed = newTurnSpeed;
}

void Player::SetUpwardSpeed(float newUpwardSpeed)
{
	upwardSpeed = newUpwardSpeed;
}

void Player::SetIsInAir(bool bIsInAir)
{
	isInAir = bIsInAir;
}


void Player::SetSpeed(float newSpeed)
{
	currentSpeed = newSpeed;
}

static float toRadians(float degree)
{
	return degree * PI / 180.0f;
}
