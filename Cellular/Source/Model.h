#pragma once
#include "CEngine.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "Mesh.h"

class Model
{
public:

	Model(std::string const &path, bool gamma = false);

	void Render(const Shader& shader);

private:

	void LoadModel(const std::string& path);
	void ProcessNode(aiNode *node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<TextureData> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);


private:

	std::vector<Mesh>	Meshes;
	std::vector<TextureData>		textures_loaded;
	bool				gammaCorrection;
	std::string			directory;;

};