#ifndef MESH2_H
#define MESH2_H

#include <glm\glm.hpp>
#include <GL/glew.h>
#include <string>
#include "obj_loader.h"
#include "Terrain.h"

using namespace std;

class Vertex
{
public:
	Vertex(const glm::vec3& position = glm::vec3(0.0), const glm::vec2& textureCoord = glm::vec2(0.0)) :
		pos(position),
		texCoord(textureCoord) {}
	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
	

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
};

class Mesh
{
public:
	
	Mesh(Vertex* vertices, unsigned int numVertices);
	Mesh(const string& fileName);
	Mesh(Terrain terrain);
	Mesh();
	
	void Draw();
	void GuiDraw();
	void SkyboxDraw();
	~Mesh();
private:
	void initMesh(const IndexedModel& model);
	
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFER
	};

	// reference to vertex array object
	GLuint m_glVertexArrayObject;
	GLuint m_glVertexArrayBuffers[NUM_BUFFER];

	unsigned int  draw_count;
};

#endif // !MESH2_H

