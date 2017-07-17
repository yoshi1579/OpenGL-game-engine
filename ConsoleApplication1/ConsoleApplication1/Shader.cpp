#include "Shader.h"
#include <fstream>
#include <glm\glm.hpp>
#include "Texture.h"

using namespace std;

static string LoadSourceFile(const string& fileName);
static GLuint CreateShader(const string& sourceName, GLenum shaderType);
static void CheckCompilerError(GLuint shaderObject);
static void CheckLinkerError(GLuint shaderObject);
static void CheckValidationError(GLuint shaderObject);

Shader::Shader(const string& sourcePath)
{
	shaderProgram = glCreateProgram();
	shaders[0] = CreateShader(LoadSourceFile(sourcePath + ".vs.txt"), GL_VERTEX_SHADER);
	shaders[1] = CreateShader(LoadSourceFile(sourcePath + ".fs.txt"), GL_FRAGMENT_SHADER);

	for (int i = 0; i < NUM_SHADER; i++)
	{
		glAttachShader(shaderProgram, shaders[i]);
	}
	glBindAttribLocation(shaderProgram, 0, "position");
	glBindAttribLocation(shaderProgram, 1, "texCoord");
	glBindAttribLocation(shaderProgram, 2, "normal");
	glLinkProgram(shaderProgram);
	CheckLinkerError(shaderProgram);
	glValidateProgram(shaderProgram);
	CheckValidationError(shaderProgram);
	uniforms[TRANSFORM] = glGetUniformLocation(shaderProgram, "transMatrix");
	uniforms[PROJECTION] = glGetUniformLocation(shaderProgram, "projectionMatirx");
	uniforms[LIGHTPOS] = glGetUniformLocation(shaderProgram, "lightPosition");
	uniforms[LIGHTCOL] = glGetUniformLocation(shaderProgram, "lightColor");
	uniforms[CAMERAPOS] = glGetUniformLocation(shaderProgram, "cameraPos");
	uniforms[REFLECTIVITY] = glGetUniformLocation(shaderProgram, "reflectivity");
	uniforms[SHADERDUMP] = glGetUniformLocation(shaderProgram, "shaderDump");
	uniforms[FAKENORMAL] = glGetUniformLocation(shaderProgram, "needFakeNormal");
	uniforms[SKYCOLOR] = glGetUniformLocation(shaderProgram, "skyColor");
	uniforms[TERRAIN_TEX_R] = glGetUniformLocation(shaderProgram, "dirtTexture");
	uniforms[TERRAIN_TEX_G] = glGetUniformLocation(shaderProgram, "flowerTexture");
	uniforms[TERRAIN_TEX_B] = glGetUniformLocation(shaderProgram, "tileTexture");
	uniforms[TERRAIN_TEX_BACK] = glGetUniformLocation(shaderProgram, "grassTexture");
	uniforms[BLENDMAP_TEX] = glGetUniformLocation(shaderProgram, "blendMapTexture");
}

Shader::Shader()
{
}

Shader::~Shader()
{
	for (int i = 0; i < NUM_SHADER; i++)
	{
		glDetachShader(shaderProgram, shaders[i]);
		glDeleteShader(shaders[i]);
	}
	glDeleteProgram(shaderProgram);
}

void Shader::Bind()
{
	glUseProgram(shaderProgram);
}

void Shader::terrainTexUniformBind()
{
	glUniform1i(uniforms[TERRAIN_TEX_BACK], 0);
	glUniform1i(uniforms[TERRAIN_TEX_R], 1);
	glUniform1i(uniforms[TERRAIN_TEX_G], 2);
	glUniform1i(uniforms[TERRAIN_TEX_B], 3);
	glUniform1i(uniforms[BLENDMAP_TEX], 4);
}

void Shader::Update(const Transform & transform, Camera camera, 
	const glm::vec3& lightPos, const glm::vec3& lightCol, 
	const float& reflectivity, const float& shineDump, const float& needFakeNormal, const glm::vec3& skyColor)
{
	glm::vec3 cameraPos = camera.GetPos();
	glUniformMatrix4fv(uniforms[TRANSFORM], 1, GL_FALSE, &transform.GetModel()[0][0]);
	glUniformMatrix4fv(uniforms[PROJECTION], 1, GL_FALSE, &camera.GetViewProjection()[0][0]);
	glUniform3fv(uniforms[LIGHTPOS], 1, &lightPos[0]);
	glUniform3fv(uniforms[LIGHTCOL], 1, &lightCol[0]);
	glUniform3fv(uniforms[CAMERAPOS], 1, &cameraPos[0]);
	glUniform1fv(uniforms[REFLECTIVITY], 1, &reflectivity);
	glUniform1fv(uniforms[SHADERDUMP], 1, &shineDump);
	glUniform1fv(uniforms[FAKENORMAL], 1, &needFakeNormal);
	glUniform3fv(uniforms[SKYCOLOR], 1, &skyColor[0]);
	glUniform1i(uniforms[TERRAIN_TEX_BACK], 0);
	glUniform1i(uniforms[TERRAIN_TEX_R], 1);
	glUniform1i(uniforms[TERRAIN_TEX_G], 2);
	glUniform1i(uniforms[TERRAIN_TEX_B], 3);
	glUniform1i(uniforms[BLENDMAP_TEX], 4);
}

static GLuint CreateShader(const string& source, GLenum shaderType)
{
	GLuint shaderObject = glCreateShader(shaderType);
	if (shaderObject == 0)
	{
		cerr << "Error: shader object creation fail" << endl;
	}
	const GLchar * shaderSource[1];
	GLint shaderSourceLength[1];
	shaderSource[0] = source.c_str();
	shaderSourceLength[0] = source.length();
	glShaderSource(shaderObject, 1, shaderSource, shaderSourceLength);
	glCompileShader(shaderObject);
	CheckCompilerError(shaderObject);
	
	return shaderObject;
}

static void CheckCompilerError(GLuint shaderObject)
{
	GLint status = 0;
	char error[1024] = { 0 };
	GLsizei length = 0;
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderInfoLog(shaderObject, sizeof(error), &length, error);
		cerr << "Shader Compilation Error: " << error << endl;
	}
}

static void CheckLinkerError(GLuint shaderObject)
{
	GLint status = 0;
	char error[1024] = { 0 };
	GLsizei length = 0;
	glGetProgramiv(shaderObject, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetProgramInfoLog(shaderObject, sizeof(error), &length, error);
		cerr << "Shader Linking Error: " << error << endl;
	}
}

static void CheckValidationError(GLuint shaderObject)
{
	GLint status = 0;
	char error[1024] = { 0 };
	GLsizei length = 0;
	glGetProgramiv(shaderObject, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetProgramInfoLog(shaderObject, sizeof(error), &length, error);
		cerr << "Shader Validation Error: " << error << endl;
	}
}

static string LoadSourceFile(const string& fileName)
{
	ifstream file;
	file.open((fileName).c_str());

	string output;
	string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		cerr << "Unable to load shader: " << fileName << endl;
	}
	return output;
}
