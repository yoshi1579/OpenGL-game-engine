#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(Shader * entityShader, Texture * entityTexture, Mesh * entityMesh, list<Transform> entityTransforms)
{
	texture = entityTexture;
	shader = entityShader;
	mesh = entityMesh;
	transforms = entityTransforms;
}

void Entity::increseRotation(glm::vec3 rotation)
{
	transforms.front().GetRot() += rotation;
}

void Entity::increasePosition(glm::vec3 position)
{
	transforms.front().GetPos() += position;
}

glm::vec3 Entity::GetRotation()
{
	return transforms.front().GetRot();
}

glm::vec3 Entity::GetPosition()
{
	return transforms.front().GetPos();
}

void Entity::SetPositionY(float posY)
{
	transforms.front().GetPos().y = posY;
}
