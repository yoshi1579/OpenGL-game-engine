#include "terrain_texture.h"


TerrainTextures::TerrainTextures()
{
}

TerrainTextures::TerrainTextures(string grassTex, string dirtTex, string flowerTex, string tileTex)
{
	static Texture grassT(grassTex, false, false);
	static Texture dirtT(dirtTex, false, false);
	static Texture flowerT(flowerTex, false, false);
	static Texture tileT(tileTex, false, false);

	grassTexture = grassT;
	dirtTexture = dirtT;
	flowerTexture = flowerT;
	tileTexture = tileT;
}
