#include "TextureManager.h"
#include "CEngine.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	for (auto It = TextureMap.begin(); It != TextureMap.end(); ++It)
	{
		delete It->second;
	}

	TextureMap.clear();
}

TextureManager& TextureManager::GetInstance()
{
	static TextureManager Instance;
	return Instance;
}

void TextureManager::LoadTexture(const std::string & fileName)
{
	unsigned int TextureID;
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int Width, Height, nrChannels;
	unsigned char *Data = stbi_load(fileName.c_str(), &Width, &Height, &nrChannels, 0);

	if (Data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
		glGenerateMipmap(GL_TEXTURE_2D);

		TextureMap.insert({ fileName, new Texture(TextureID, Width, Height) });
	}
	else
	{
		C_LOG("Failed to load TextureManager\n");
	}

	stbi_image_free(Data);
}
