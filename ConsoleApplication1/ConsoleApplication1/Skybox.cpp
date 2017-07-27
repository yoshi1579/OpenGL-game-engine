#include "Skybox.h"

Skybox::Skybox(string right, string left, string top, string bottom, string front, string back)
{
	nameTextures[0] = right;
	nameTextures[1] = left;
	nameTextures[2] = top;
	nameTextures[3] = bottom;
	nameTextures[4] = front;
	nameTextures[5] = back;

	shader = Shader("./res/skyboxShader");
	mesh = Mesh(vertices, 36);
	texture = Texture(nameTextures, false, false);
}

void Skybox::Render(Camera camera)
{
	shader.Bind();
	shader.SkyboxUpdate(camera);
	texture.Bind(GL_TEXTURE0, false);
	mesh.SkyboxDraw();
	
	//guiMesh.GuiDraw();
}
