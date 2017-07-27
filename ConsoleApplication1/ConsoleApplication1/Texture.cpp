#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>
using namespace std;

Texture::Texture(const string& fileName, bool bTransparency, bool bFakeNormal)
{
	int width, height, numComponets;
	hasTransparency = bTransparency;
	needFakeNormal = bFakeNormal;
	
	// loading stb image
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponets, 4);
	if (imageData == NULL)
	{
		cerr << "Texture loading fail: " << fileName << endl;
	}

	// generate 1 texture space in GPU
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	//Control texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	// mipmapping
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1);

	stbi_image_free(imageData);

}

Texture::Texture(string * fileNames, bool bTransparency, bool bFakeNormal)
{
	int width, height, numComponets;
	hasTransparency = bTransparency;
	needFakeNormal = bFakeNormal;
	unsigned char* imageData[6];

	// generate 1 texture space in GPU
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

	for (int i = 0; i < 6; i++)
	{
		// loading stb image
		imageData[i] = stbi_load(("./res/" + fileNames[i] + ".png").c_str(), &width, &height, &numComponets, 4);
		if (imageData == NULL)
			cerr << "Texture loading fail: " << fileNames[i] << endl;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData[i]);
		//stbi_image_free(imageData);
	}
	
	//Control texture wrapping
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	for (int i = 0; i < 6; i++)
		stbi_image_free(imageData[i]);
	
}

Texture::Texture()
{
}

void Texture::SetBackFaceCull()
{
	if (hasTransparency)
	{
		glDisable(GL_CULL_FACE);
	}
}

void Texture::SetNumOfRows(int numRow)
{
	textureRows = numRow;
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind(GLenum unit, bool is2D)
{

	// set which texture you are working with
	glActiveTexture(unit);
	// binding texture
	if (is2D)
		glBindTexture(GL_TEXTURE_2D, m_texture);
	else
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
}