#pragma once
#include "CEngine.h"
#include <vector>


struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct TextureData {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:

	Mesh(std::vector<Vertex> Vertices, std::vector<unsigned int> Indices, std::vector<TextureData> Textures);
	~Mesh();

	void Render(const Shader &shader);
	const unsigned int& GetVAO() { return VAO; }

private:
	void InitMesh();


	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	unsigned int VertCount;


	// mesh data
	std::vector<Vertex>       Vertices;
	std::vector<unsigned int> Indices;
	std::vector<TextureData>  Textures;


};