#pragma once
#include "CEngine.h"

class Shader
{
public:
	
	Shader() = default;
	Shader(const std::string& filepath);
	

	inline unsigned int GetShaderprogramID()const { return ShaderProgram; }

	void SetBool(const std::string& Name, bool Value)const;
	void SetInt(const std::string& Name, int Value)const;
	void SetFloat(const std::string& Name, float Value)const;
	void SetVec3(const std::string& Name, float X, float Y, float Z)const;
	void SetMat4(const std::string& Name, const glm::mat4& mat)const;

private:

	std::string GetFileAsString(const std::string& filepath) const;

	unsigned int CreateShader(unsigned int Type,const std::string& Source);

	unsigned int ShaderProgram;
};