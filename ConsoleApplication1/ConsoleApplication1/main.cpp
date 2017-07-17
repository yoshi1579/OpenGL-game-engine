
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "camera.h"
#include <GL\glew.h>
#include "Mesh2.h"
#include <vector>
#include "transform.h"
#include "Player.h"
#include <stdlib.h>
#include "Terrain.h"
#include <list>
#include "Entity.h"
#include "FrameTime.h"


struct RandomObj
{
	Mesh mesh;
	Transform transform;
};

struct Obj
{
	Shader* shader;
	Texture* texture;
	Mesh* mesh;
	list<Transform> transforms;
};

enum
{
	TREE,
	GRASS,
	FERN,
	PLAYER,
	NUM_OBJ
};


static void SetEntityArray(Entity** arrayObjs, int index, Entity* entity);
static list<Transform> RandomTransformGenerate(int num, float scale, Terrain* terrain);
static double clockToMilliseconds(clock_t ticks);

#define WIDTH 800
#define HEIGHT 600
#define RED 0.5f
#define BLUE 0.5f
#define GREEN 0.5f

using namespace std;


int main(int argc, char** argv)
{
	// FPS
	// initialize FPS
	FrameTime frameTime(60.0);

	Entity* arrayObjs[NUM_OBJ];
	
	glm::vec3 cameraPos = glm::vec3(0, 10, -18.0f);
	glm::vec3 skyColor = glm::vec3(RED, GREEN, BLUE);
	float shineDump = 10;
	float reflectivity = 1;
	Window window(WIDTH, HEIGHT, "First Window");


	Shader terrainShader("./res/terrainBasicShader");
	Shader objShader("./res/basicShader");

	//terrain 
	TerrainTextures terrainTexture("./res/grass.png", "./res/mud.png", "./res/grassFlowers.png", "./res/path.png");
	Texture blendMapTex("./res/path.png", false, false);
	Texture blendMapTexY("./res/blendMap.png", false, false);
	Texture terrainTextureR("./res/mud.png", false, false);
	Texture terrainTextureG("./res/grassFlowers.png", false, false);
	Texture terrainTextureB("./res/path.png", false, false);
	Texture terrainTextureBack("./res/grass.png", false, false);
	Terrain terrain(0, 0, blendMapTex, terrainTexture, "./res/heightmap.png");
	//Terrain terrain2(1, 0, blendMapTex, terrainTexture, "./res/heightmap.png");

	Transform terrainTransform;
	terrainTransform.GetPos().x = terrain.GetPosX();
	terrainTransform.GetPos().z = terrain.GetPosZ();
	//Transform terrainTransform2;
	//terrainTransform2.GetPos().x = terrain2.GetPosX();
	//terrainTransform2.GetPos().z = terrain2.GetPosZ();
	Mesh terrainMesh(terrain);
	//Mesh terrainMesh2(terrain2);

	// glass
	Texture glassTexture("./res/grassTexture.png", true, true);
	Mesh glassMesh("./res/grassModel.obj");
	Entity grassEntity(&objShader, &glassTexture, &glassMesh, RandomTransformGenerate(200, 1.0, &terrain));
	SetEntityArray(&arrayObjs[0], GRASS, &grassEntity);

	// fern
	Texture fernTexture("./res/fern.png", true, false);
	Mesh fernMesh("./res/fern.obj");
	Entity fernEntity(&objShader, &fernTexture, &fernMesh, RandomTransformGenerate(200, 1.0, &terrain));
	SetEntityArray(&arrayObjs[0], FERN, &fernEntity);

	// tree
	Texture treeTexture("./res/tree.png", false, false);
	Mesh treeMesh("./res/tree.obj");
	Entity treeEntity(&objShader, &treeTexture, &treeMesh, RandomTransformGenerate(200, 5.0, &terrain));
	SetEntityArray(&arrayObjs[0], TREE, &treeEntity);

	// player
	Texture playerTexture("./res/bricks.jpg", false, false);
	Mesh playerMesh("./res/monkey3.obj");
	list<Transform> ptransforms;
	Transform ptransform;
	ptransform.GetPos().x = 0;
	ptransform.GetPos().z = 0;
	ptransform.SetScale(glm::vec3(5, 5, 5));
	ptransforms.push_back(ptransform);
	Player playerEntity(&objShader, &playerTexture, &playerMesh, ptransforms, 0, 0);
	SetEntityArray(&arrayObjs[0], PLAYER, &playerEntity);
	
	
	Camera camera(cameraPos, 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f, 50);
	Transform transform;
	
	float counter = 0;
	int count = 0;

	while (!window.GetbClosed())
	{
		// calculate FPS
		frameTime.CalculateFPS();
		if (count >= 10)
		{
			cout << frameTime.fps << endl;
			count = 0;
		}
		count++;

		glClearColor(RED, GREEN, BLUE, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw terrain 

		terrainShader.Bind();
		terrainShader.terrainTexUniformBind();
		//terrain.BindTexture();
		terrainTextureBack.Bind(GL_TEXTURE0);
		terrainTextureR.Bind(GL_TEXTURE1);
		terrainTextureG.Bind(GL_TEXTURE2);
		terrainTextureB.Bind(GL_TEXTURE3);
		blendMapTexY.Bind(GL_TEXTURE4);
		terrainShader.Update(terrainTransform, camera, glm::vec3(0, 1000, 30), glm::vec3(1, 1, 1), 
								reflectivity, shineDump, blendMapTex.GetNeedFakeNormal(), skyColor);
		terrainMesh.Draw();
		//terrainShader.Update(terrainTransform2, camera, glm::vec3(0, 1000, 30), glm::vec3(1, 1, 1), 
								//reflectivity, shineDump, blendMapTex.GetNeedFakeNormal(), skyColor);
		//terrainMesh2.Draw();
		
		for (int i = 0; i < NUM_OBJ; i++)
		{
			arrayObjs[i]->texture->Bind(GL_TEXTURE0);
			arrayObjs[i]->shader->Bind();
			
			for (list<Transform>::iterator it = arrayObjs[i]->transforms.begin(); it != arrayObjs[i]->transforms.end(); ++it)
			{
				arrayObjs[i]->texture->SetBackFaceCull();
				arrayObjs[i]->shader->Update(*it, camera, glm::vec3(0, 1000, 30), glm::vec3(1, 1, 1), reflectivity, shineDump, arrayObjs[i]->texture->GetNeedFakeNormal(), skyColor);
				arrayObjs[i]->mesh->Draw();
			}
		}
		
		playerEntity.move(frameTime.fps, &terrain);
		camera.CameraMove(&playerEntity);
		window.SwapBuffer(&camera, &playerEntity);
		
		counter += 0.01f;
	}

	terrain.~Terrain();
	window.~Window();

	return 0;
}

static void SetEntityArray(Entity** arrayObjs, int index, Entity* entity)
{
	arrayObjs[index] = entity;
}

static list<Transform> RandomTransformGenerate(int num, float scale, Terrain* terrain)
{
	list<Transform> transforms;
	for (int i = 0; i < num; i++)
	{
		Transform transform;
		float posX = rand() % 1000;
		float posZ = rand() % 1000;
		transform.GetPos().x = posX;
		transform.GetPos().z = posZ;
		transform.GetPos().y = terrain->GetTerrainHeight(posX, posZ);
		transform.SetScale(glm::vec3(scale, scale, scale));
		transforms.push_back(transform);
	}

	return transforms;
}

static double clockToMilliseconds(clock_t ticks)
{
	return (ticks / (double)CLOCKS_PER_SEC) * 1000.0;
}