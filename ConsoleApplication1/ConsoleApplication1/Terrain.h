
#ifndef TERRAIN_H
#define TERRAIN_H

#include "obj_loader.h"
#include "Texture.h"
#include "terrain_texture.h"

static float SIZE = 800;
const static int VERTEX_COUNT = 256;
static float heights[VERTEX_COUNT][VERTEX_COUNT];

class Terrain
{
private:
	float x;
	float z;
	Texture blendMapTexture;
	TerrainTextures terrainTextures;
	unsigned char* hightMap;
	
	int heightMap_height, heightMap_width, hegihtMap_numComponets;

	float GetHeight(int x, int y, unsigned char* heightMap);
	
	glm::vec3 CalculateNormal(int x, int y, unsigned char* heightMap);
public:
	inline float GetPosX() { return x; }
	inline float GetPosZ() { return z; }
	inline TerrainTextures* GetTerrainTextures() { return &terrainTextures; }
	inline Texture* GetBlendMapTexture() { return &blendMapTexture; }
	Terrain(float x, float z,const Texture& blendMapTexture, const TerrainTextures& terrainTextures, const string& fileHightMap);
	IndexedModel generateTerrain();
	float GetTerrainHeight(float worldX, float worldZ);
	void BindTexture();
	~Terrain();
};
#endif // !TERRAIN_H

