#ifndef  TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>
using namespace std;

class Texture
{
public:
	Texture(const string& fileName, bool bTransparency, bool bFakeNormal);
	Texture(string* fileNames, bool bTransparency, bool bFakeNormal);
	Texture();
	Texture(const Texture& other)
	{
		m_texture = other.m_texture;
		hasTransparency = other.hasTransparency;
		needFakeNormal = other.needFakeNormal;
	}

	void swapTexture(Texture& first, Texture& second)
	{
		swap(first.m_texture, second.m_texture);
		swap(first.hasTransparency, second.hasTransparency);
		swap(first.needFakeNormal, second.needFakeNormal);
	}
	Texture& operator =(Texture other) 
	{
		swapTexture(*this, other);
		return *this;
	}

	// set openGL to start using whatever texture, unit is how many textures I want to bind
	void Bind(GLenum uint, bool is2D);
	void SetBackFaceCull();
	void SetNumOfRows(int numRow);

	inline void SetHasTransparency() { hasTransparency = true; }
	inline void SetNeedFakeNormal(bool bFakeNormal) { needFakeNormal = bFakeNormal;  }
	inline bool GetNeedFakeNormal() { return needFakeNormal; }
	inline int GetTextureRows() { return textureRows; }
	virtual ~Texture();
private:

	GLuint m_texture;
	bool hasTransparency = false;
	bool needFakeNormal = false;
	int textureRows = 1; 
};
#endif // ! TECTURE_H

