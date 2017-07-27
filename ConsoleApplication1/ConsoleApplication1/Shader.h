#ifndef SHADER_H
#define SHADER_H

#include <GL\glew.h>
#include <iostream>
#include <string>
#include <list>
#include "transform.h"
#include "camera.h"
#include "Light.h"

const int MAX_LIGHTS = 4;

using namespace std;

class Shader
{
public:
	Shader(const string&  source);
	Shader();
	~Shader();
	void Bind();
	void terrainTexUniformBind();
	void Update(const Transform& transform, Camera camera, 
		list<Light> lights, 
		const float& reflectivity, const float& shineDump, const float& needFakeNormal, 
		const glm::vec3& skyColor, const float& texNumRow, const glm::vec2& texOffset);
	void GuiUpdate(const Transform& transform);
	void SkyboxUpdate(Camera camera);
protected:
private:
	enum 
	{
		TRANSFORM,
		PROJECTION,
		CAMERAPOS,
		SHADERDUMP,
		REFLECTIVITY,
		FAKENORMAL,
		SKYCOLOR,
		TERRAIN_TEX_R,
		TERRAIN_TEX_G,
		TERRAIN_TEX_B,
		TERRAIN_TEX_BACK,
		BLENDMAP_TEX,
		TEXTUER_NUM_ROWS,
		TEXTUER_OFFSET,
		NUM_UNIFORM
	};
	int lightsPos[MAX_LIGHTS];
	int lightColors[MAX_LIGHTS];
	int lightAttenu[MAX_LIGHTS];

	static const int NUM_SHADER = 2;
	GLuint shaderProgram;
	GLuint shaders[NUM_SHADER];
	GLuint uniforms[NUM_UNIFORM];
};
#endif // !SHADER_H
