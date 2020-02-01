#pragma once
class Texture
{
public:
	Texture(unsigned int ID,int Width,int Height) 
	{
		this->ID		= ID;
		this->Width		= Width;
		this->Height	= Height;
	}
	inline int GetTextureID()const { return ID; }
	inline int GetWidth()const { return Width; }
	inline int GetHeight()const { return Height; }


private:
	unsigned int ID;
	int Width;
	int Height;
};