#pragma once
#include "CEngine.h"
#include <vector>


struct Vertex {
	glm::vec3 Position;
	glm::vec2 TexCoords;
};


class Mesh
{
public:

	Mesh();
	~Mesh();

	void InitMesh(std::vector<Vertex> Vertices);
	void Render();
	const unsigned int& GetVAO() { return VAO; }

private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int VertCount;
};