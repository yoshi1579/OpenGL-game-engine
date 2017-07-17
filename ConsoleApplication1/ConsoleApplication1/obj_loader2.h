#ifndef OBJ_LOADER2_H
#define OBJ_LOADER2_H

#include <vector>
#include <glm\glm.hpp>
#include <string>

using namespace std;

class OBJModel
{
public:
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	glm::vec3 ParseOBJVec3(char* line);
	glm::vec2 ParseOBJVec2(char* line);
	void ParseOBJIndices(char * line, std::vector<glm::vec3> temp_positions, std::vector<glm::vec2> temp_textures, std::vector<glm::vec3> temp_normals);

	OBJModel(const string& filePath);
};

#endif // !OBJ_LOADER2_H

