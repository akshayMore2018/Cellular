#pragma once
#include <map>
#include "Texture.h"
#include <Vector>

class TextureManager
{
	TextureManager(); // prevent construction from outside
	TextureManager(const TextureManager&);//prevent construction by copying
	TextureManager& operator=(const TextureManager&); //prevent assignment
	~TextureManager();

public:
	static TextureManager& GetInstance();

	void LoadTexture(const std::string& fileName);
	unsigned int LoadCubeMap(const std::vector<std::string>& faces);
	
	std::map<std::string, Texture*> TextureMap;
};