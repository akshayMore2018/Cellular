#pragma once
#include <iostream>

class Shader
{
public:

	Shader(const std::string& filepath);

	inline unsigned int GetShaderprogramID()const { return ShaderProgram; }

private:

	std::string GetFileAsString(const std::string& filepath) const;

	unsigned int CreateShader(unsigned int Type,const std::string& Source);

	unsigned int ShaderProgram;
};