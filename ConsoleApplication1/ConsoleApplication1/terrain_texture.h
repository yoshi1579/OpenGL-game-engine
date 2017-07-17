
#ifndef TERRAIN_TEXTURE_H
#define TERRAIN_TEXTURE_H

#include <iostream>
#include "Texture.h"

using namespace std;

class TerrainTextures
{
public:
	Texture grassTexture;
	Texture dirtTexture;
	Texture flowerTexture;
	Texture tileTexture;

	TerrainTextures();
	TerrainTextures(string glassTex, string dirtTex, string flowerTex, string tileTex);
	TerrainTextures(const TerrainTextures& other)
	{
		grassTexture = other.grassTexture;
		dirtTexture = other.dirtTexture;
		flowerTexture = other.flowerTexture;
		tileTexture = other.tileTexture;
	}

	void swapTerrainTexture(TerrainTextures& first, TerrainTextures& second)
	{
		swap(first.grassTexture, second.grassTexture);
		swap(first.dirtTexture, second.dirtTexture);
		swap(first.flowerTexture, second.flowerTexture);
		swap(first.tileTexture, second.tileTexture);
	}
	TerrainTextures& operator =(TerrainTextures other)
	{
		swapTerrainTexture(*this, other);
		return *this;
	}
};

#endif // !TERRAIN_TEXTURE_H
