#include "Terrain.h"
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <math.h>
#include "stb_image.h"
#include "Texture.h"
#include "Shader.h"

static float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);

Terrain::Terrain(float xValue, float zValue,const Texture& blendMapTex, const TerrainTextures& terrainTex, const string& fileHightMap)
{
	x = xValue * SIZE;
	z = zValue * SIZE;
	blendMapTexture = blendMapTex;
	terrainTextures = terrainTex;
	hightMap = stbi_load(fileHightMap.c_str(), &heightMap_width, &heightMap_height, &hegihtMap_numComponets, 4);
	if (hightMap == NULL)
	{
		cerr << "Texture loading fail: " << fileHightMap << endl;
	}
}

IndexedModel Terrain::generateTerrain()
{
	IndexedModel indexedModel;
	//int VERTEX_COUNT = heightMap_height;
	
	int count = VERTEX_COUNT * VERTEX_COUNT;
	int terrainHeight = 0;
	glm::vec3 normal;

	//heights = new float*[VERTEX_COUNT];
	for (int i = 0; i<VERTEX_COUNT; i++) {
		//heights[i] = new float[VERTEX_COUNT];
		for (int j = 0; j<VERTEX_COUNT; j++) {
			terrainHeight = GetHeight(i, j, hightMap);


			heights[j][i] = terrainHeight;

			normal = CalculateNormal(i, j, hightMap);
			indexedModel.positions.push_back(glm::vec3((float)j / ((float)VERTEX_COUNT - 1) * SIZE, terrainHeight, (float)i / ((float)VERTEX_COUNT - 1) * SIZE));
			indexedModel.normals.push_back(normal);
			indexedModel.texCoords.push_back(glm::vec2((float)j / ((float)VERTEX_COUNT - 1), (float)i / ((float)VERTEX_COUNT - 1)));
		}
	}
	for (int gz = 0; gz<VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx<VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indexedModel.indices.push_back(topLeft);
			indexedModel.indices.push_back(bottomLeft);
			indexedModel.indices.push_back(topRight);
			indexedModel.indices.push_back(topRight);
			indexedModel.indices.push_back(bottomLeft);
			indexedModel.indices.push_back(bottomRight);
		}
	}
	return indexedModel;
}

void Terrain::BindTexture()
{
	terrainTextures.grassTexture.Bind(0, true);
	//terrainTextures.dirtTexture.Bind(1);
	terrainTextures.flowerTexture.Bind(2, true);
	terrainTextures.tileTexture.Bind(3, true);
	blendMapTexture.Bind(4, true);
}

Terrain::~Terrain()
{

}

float Terrain::GetHeight(int x, int y, unsigned char* heightMap)
{
	if (x < 0 || x >= heightMap_height || y < 0 || y >= heightMap_height)
		return 0;
	float terrainHeight = heightMap[heightMap_width * x * 4 + y * 4];
	terrainHeight = terrainHeight * 80 / 256;
	terrainHeight -= 40;
	return terrainHeight;
}


float Terrain::GetTerrainHeight(float worldX, float worldZ)
{
	float terrainX = worldX - x;
	float terrainZ = worldZ - z;
	float gridSquareSize = SIZE / ((float)VERTEX_COUNT - 1);
	int gridX = (int)floor(terrainX / gridSquareSize);
	int gridZ = (int)floor(terrainZ / gridSquareSize);
	
	if (gridX >= VERTEX_COUNT - 1 || gridZ >= VERTEX_COUNT - 1 || gridX < 0 || gridZ < 0)
	{
		return 0;
	}

	float xCoord = (terrainX - (float)gridX * gridSquareSize) / gridSquareSize;
	float zCoord = (terrainZ - (float)gridZ * gridSquareSize) / gridSquareSize;

	float answer = 0;
	if (xCoord <= (1 - zCoord)) {
		answer = barryCentric(	glm::vec3(0, heights[gridX][gridZ], 0), 
								glm::vec3(1, heights[gridX + 1][gridZ], 0), 
								glm::vec3(0, heights[gridX][gridZ + 1], 1), 
								glm::vec2(xCoord, zCoord));
	}
	else {
		answer = barryCentric(	glm::vec3(1, heights[gridX + 1][gridZ], 0), 
								glm::vec3(1, heights[gridX + 1][gridZ + 1], 1), 
								glm::vec3(0, heights[gridX][gridZ + 1], 1), 
								glm::vec2(xCoord, zCoord));
	}
	return answer;
}


glm::vec3 Terrain::CalculateNormal(int x, int y, unsigned char * heightMap)
{
	float heightL = GetHeight(x - 1, y, heightMap);
	float heightR = GetHeight(x + 1, y, heightMap);
	float heightD = GetHeight(x, y - 1, heightMap);
	float heightU = GetHeight(x, y + 1, heightMap);
	
	return glm::normalize(glm::vec3(heightL - heightR, 2.0f, heightD - heightU));
}


static float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) 
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}