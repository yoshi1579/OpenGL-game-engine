#ifndef SHADER_H
#define SHADER_H

#include <GL\glew.h>
#include <iostream>
#include <string>
#include "transform.h"
#include "camera.h"

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
		const glm::vec3& lightPos, const glm::vec3& lightCol, 
		const float& reflectivity, const float& shineDump, const float& needFakeNormal, const glm::vec3& skyColor);
protected:
private:
	enum 
	{
		TRANSFORM,
		PROJECTION,
		LIGHTPOS,
		LIGHTCOL,
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
		NUM_UNIFORM
	};
	static const int NUM_SHADER = 2;
	GLuint shaderProgram;
	GLuint shaders[NUM_SHADER];
	GLuint uniforms[NUM_UNIFORM];
};
#endif // !SHADER_H
