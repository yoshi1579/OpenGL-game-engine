#ifndef SKYBOX_H
#define SKYBOX_H

#include <string>
#include "Mesh2.h"
#include "Shader.h"

using namespace std;
const float SKYBOX_SIZE = 500;

class Skybox
{
private:
	Vertex vertices[36] = {
		Vertex(glm::vec3(-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE)),
		Vertex(glm::vec3(-SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE)),
		Vertex(glm::vec3(SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE)),
		Vertex(glm::vec3(SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE)),
		Vertex(glm::vec3(SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE)),
		Vertex(glm::vec3(-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE)),

		Vertex(glm::vec3(-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE)),
		Vertex(glm::vec3(-SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE)),
		Vertex(glm::vec3(-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE)),
		Vertex(glm::vec3(-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE)),
		Vertex(glm::vec3(-SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE)),
		Vertex(glm::vec3(-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE)),

		Vertex(glm::vec3(SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE)),
		Vertex(glm::vec3(SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE)),
		Vertex(glm::vec3(SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE)),
		Vertex(glm::vec3(SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE)),
		Vertex(glm::vec3(SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE)),
		Vertex(glm::vec3(SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE)),

		Vertex(glm::vec3(-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE)),
		Vertex(glm::vec3(-SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE)),
		Vertex(glm::vec3(SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE)),
		Vertex(glm::vec3(SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE)),
		Vertex(glm::vec3(SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE)),
		Vertex(glm::vec3(-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE)),

		Vertex(glm::vec3(-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE)),
		Vertex(glm::vec3(SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE)),
		Vertex(glm::vec3(SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE)),
		Vertex(glm::vec3(SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE)),
		Vertex(glm::vec3(-SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE)),
		Vertex(glm::vec3(-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE)),

		Vertex(glm::vec3(-SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE)),
		Vertex(glm::vec3(-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE)),
		Vertex(glm::vec3(SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE)),
		Vertex(glm::vec3(SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE)),
		Vertex(glm::vec3(-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE)),
		Vertex(glm::vec3(SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE)) 
	};

	string nameTextures[6];
	Shader shader;
	Mesh mesh;
	Texture texture;
public:
	Skybox(string right, string left, string top, string bottom, string front, string back);
	inline Vertex* GetVertices() { return vertices; }
	inline string* GetTextures() { return nameTextures; }

	void Render(Camera camera);
};
#endif // !SKYBOX_H

