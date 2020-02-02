#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Mesh::InitMesh(std::vector<Vertex> Vertices)
{
	VertCount = Vertices.size();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);// Bind the VAO and any subsequent vertex attribute calls from this point on will be stored inside the VAO.

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex),&Vertices[0], GL_STATIC_DRAW);

	//position attrib
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	//texture attrib
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, TexCoords)));
	glEnableVertexAttribArray(1);

}

void Mesh::Render()
{
	glDrawArrays(GL_TRIANGLES, 0, VertCount);
}
