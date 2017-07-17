
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Window.h"

const float RUN_SPEED = 0.035;
const float TURN_SPEED = 0.002;
const float GRAVITY = -50;
const float JUMP_POWER = 30;
const float TERRAIN_HEIGHT = 0;

class Player : public Entity
{
public:
	Player();
	Player(Shader* shader, Texture* texture, Mesh* mesh, list<Transform> transforms, float speed, float turnSpeed)
		:Entity(shader, texture, mesh, transforms)
	{
		currentSpeed = speed;
		currentTurnSpeed = turnSpeed;
	}

	inline void SetCurrentSpeed(float speed) { currentSpeed = speed; }
	inline bool GetIsInAir() { return isInAir; }
	void move(double fps, Terrain* terrain);
	void SetSpeed(float newSpeed);
	void SetCurrentTurnSpeed(float newTurnSpeed);
	void SetUpwardSpeed(float newUpwardSpeed);
	void SetIsInAir(bool bIsInAir);
	
private:
	float currentSpeed;
	float currentTurnSpeed;
	float upwardSpeed = 0;
	bool isInAir = false;
};
#endif // !PLAYER_H

