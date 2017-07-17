#ifndef  RENDERER_H
#define RENDERER_H

#include <iostream>
#include <map>
#include <list>
#include "Texture.h"
#include "camera.h"
#include "Mesh2.h"
#include "Shader.h"
#include "transform.h"


using namespace std;

struct ObjData
{
	Mesh mesh;
	Transform transform;
};

struct Obj
{
	Shader shader;
	Texture* texture;
	ObjData* objData;
};

class Renderer
{
private:
	map<string, list<Obj>> entities;
public:
	void ProcessEntity(string texturePath, string meshPath);
};
#endif // ! RENDERER_H

