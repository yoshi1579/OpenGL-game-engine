#include "obj_loader2.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <cstdint>
#include <cstring>

glm::vec3 OBJModel::ParseOBJVec3(char * line)
{
	char* token = NULL;
	unsigned int i = 0;
	float values[3] = { 0,0,0 };
	token = strtok(line, " ");
	
	while (token != NULL)
	{
		values[i] = atof(token);
		i++;
		token = strtok(NULL, " ");
	}
	return glm::vec3(values[0], values[1], values[2]);
}

glm::vec2 OBJModel::ParseOBJVec2(char * line)
{
	char* token = NULL;
	unsigned int i = 0;
	float values[2] = { 0,0 };
	token = strtok(line, " ");

	while (token != NULL)
	{
		values[i] = atof(token);
		i++;
		token = strtok(NULL, " ");
	}
	return glm::vec2(values[0], values[1]);
}

void OBJModel::ParseOBJIndices(char * line, std::vector<glm::vec3> temp_positions, std::vector<glm::vec2> temp_textures, std::vector<glm::vec3> temp_normals)
{
	int values[3] = { 0,0,0 };
	int currentVertexNum = 0;
	char* token = NULL;
	int i = 0;
	token = strtok(line, "/ ");

	while (token != NULL)
	{
		values[i] = atoi(token);
		i++;
		if (i == 3)
		{
			currentVertexNum = values[0] - 1;
			positions.push_back(temp_positions.at(currentVertexNum));
			indices.push_back(currentVertexNum);
			glm::vec2 texture = temp_textures.at(values[1] - 1);
			textures.at(currentVertexNum).x = texture.x;
			textures.at(currentVertexNum).y = 1 - texture.y;
			normals.at(currentVertexNum) = temp_normals.at(values[2] - 1);
			i = 0;
		}
		token = strtok(NULL, "/ ");
	}
}

OBJModel::OBJModel(const string & filePath)
{
	int i = 0;
	std::vector<glm::vec3> temp_positions;
	std::vector<glm::vec2> temp_textures;
	std::vector<glm::vec3> temp_normals;
	std::ifstream file;
	file.open(filePath.c_str());

	std::string line;
	std::string indicator;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			unsigned int lineLength = line.length();

			if (lineLength < 2)
				continue;
			char lineCStr[100];
			char* token;
			char** numSets = NULL;
			std::strcpy(lineCStr, line.substr(2).c_str());
			indicator = line.substr(0, 2);
			//token = strtok(lineCStr, " ");

			if (indicator == "v ")
			{
				temp_positions.push_back(ParseOBJVec3(lineCStr));
			}
			else if (indicator == "vt")
			{
				temp_textures.push_back(ParseOBJVec2(lineCStr));
			}
			else if (indicator == "vn")
			{
				temp_normals.push_back(ParseOBJVec3(lineCStr));
			}
			else if(indicator == "f ")
			{
				if (i == 0)
				{
					textures = temp_textures;
					normals = temp_normals;
				}
				ParseOBJIndices(lineCStr, temp_positions, temp_textures, temp_normals);
			}

			/*
			switch (line.substr(0, 2))
			{
			case "v ":
				positions.push_back(ParseOBJVec3(line.substr(2)));
				break;
			case 'vt':
				temp_textures.push_back(ParseOBJVec2(lineCStr));
				break;
			case 'vn':
				temp_normals.push_back(ParseOBJVec3(lineCStr));
				break;
			case 'f':
				ParseOBJIndices(lineCStr, temp_textures, temp_normals);
				break;
			default: break;
			};
			*/
		}
	}
	else
	{
		std::cerr << "Unable to load mesh: " << filePath << std::endl;
	}
}
