#pragma once
#include <map>
#include "Texture.h"

class TextureManager
{
	TextureManager(); // prevent construction from outside
	TextureManager(const TextureManager&);//prevent construction by copying
	TextureManager& operator=(const TextureManager&); //prevent assignment
	~TextureManager();

public:
	static TextureManager& GetInstance();

	void LoadTexture(const std::string& fileName);
	
	std::map<std::string, Texture*> TextureMap;
};