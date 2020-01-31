#include "Shader.h"
#include <fstream>
#include <sstream>
#include "CEngine.h"

Shader::Shader(const std::string& filepath)
{
	const std::string VertexSource		= GetFileAsString(filepath+"vertex.shader");
	const std::string FragmentSource	= GetFileAsString(filepath+"fragment.shader");

	unsigned int VertexShader			= CreateShader(GL_VERTEX_SHADER, VertexSource);
	unsigned int FragmentShader			= CreateShader(GL_FRAGMENT_SHADER, FragmentSource);

	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ShaderProgram, 512, NULL, infoLog);
		C_LOG("ERROR::SHADER::PROGRAM::LINKING_FAILED\n:%s\n", infoLog);
	}
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}

void Shader::SetBool(const std::string & Name, bool Value) const
{
	glUniform1i(glGetUniformLocation(ShaderProgram, Name.c_str()), (int)Value);
}

void Shader::SetInt(const std::string & Name, int Value) const
{
	glUniform1i(glGetUniformLocation(ShaderProgram, Name.c_str()), Value);
}

void Shader::SetFloat1(const std::string & Name, float Value) const
{
	glUniform1f(glGetUniformLocation(ShaderProgram, Name.c_str()), Value);
}

void Shader::SetFloat3(const std::string & Name, float X, float Y, float Z) const
{
	glUniform3f(glGetUniformLocation(ShaderProgram, Name.c_str()), X,Y,Z);
}

std::string Shader::GetFileAsString(const std::string & filepath) const
{
	std::ifstream Stream(filepath);
	std::string line;
	std::stringstream ss;

	if (Stream.fail())
	{
		C_LOG("could not find the file : %s/n",filepath.c_str());
	}

	while (getline(Stream, line))
	{
		ss << line << "\n";
	}
	
	return ss.str();
}

unsigned int Shader::CreateShader(unsigned int Type,const std::string & Source)
{
	unsigned int ShaderID;
	const char* ShaderSource = Source.c_str();
	ShaderID = glCreateShader(Type);
	glShaderSource(ShaderID, 1, &ShaderSource, NULL);
	glCompileShader(ShaderID);

	int success;
	char infoLog[512];
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(ShaderID, 512, NULL, infoLog);
		const char* ShaderType = (Type == GL_VERTEX_SHADER) ? "VertexShader" : "FragmentShader";
		C_LOG("ERROR::SHADER:: %s ::COMPILATION_FAILED\n:%s\n", ShaderType, infoLog);
	}

	return ShaderID;
}
