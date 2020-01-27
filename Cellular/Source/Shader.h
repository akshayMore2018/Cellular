#pragma once
#include <iostream>

class Shader
{
public:

	Shader(const std::string& filepath);

	inline unsigned int GetShaderprogramID()const { return ShaderProgram; }

	void SetBool(const std::string& Name, bool Value)const;
	void SetInt(const std::string& Name, int Value)const;
	void SetFloat1(const std::string& Name, float Value)const;
	void SetFloat3(const std::string& Name, float X, float Y, float Z)const;

private:

	std::string GetFileAsString(const std::string& filepath) const;

	unsigned int CreateShader(unsigned int Type,const std::string& Source);

	unsigned int ShaderProgram;
};