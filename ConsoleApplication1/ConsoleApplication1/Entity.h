#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "Shader.h"
#include "Texture.h"
#include "Mesh2.h"
#include "transform.h"
#include <list>

using namespace std;

class Entity
{
public:
	Shader* shader;
	Texture* texture;
	Mesh* mesh;
	list<Transform> transforms;

	Entity();
	Entity(Shader* shader, Texture* texture, Mesh* mesh, list<Transform> transforms);

	void increseRotation(glm::vec3 rotation);
	void increasePosition(glm::vec3 position);
	glm::vec3 GetRotation();
	glm::vec3 GetPosition();
	void SetPositionY(float posY);

	float CalculateTextureOffsetX(int texIndex);
	float CalculateTextureOffsetY(int texIndex);
};
#endif // !ENTITY_H

