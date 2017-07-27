#ifndef LIGHT_H
#define LIGHT_H

#include "glm\glm.hpp"

class Light
{
private:
	glm::vec3 lightPosition;
	glm::vec3 lightColor;
	glm::vec3 attenuation;
public:
	Light(glm::vec3 lightPos = glm::vec3(), glm::vec3 lightCol = glm::vec3(), glm::vec3 attLight = glm::vec3(1.0, 0, 0)) :
		lightPosition(lightPos),
		lightColor(lightCol),
		attenuation(attLight){}

	inline glm::vec3 GetLightPos() { return lightPosition; }
	inline glm::vec3 GetLightColor() { return lightColor; }
	inline glm::vec3 GetAttenuation() { return attenuation; }
};
#endif // !LIGHT_H

