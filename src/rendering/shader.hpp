#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../core/math/math.hpp"
#include "../core/logger.hpp"


static bool CheckUniform(int location, const std::string &uniformName);


class Shader
{
public:
	Shader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath);
	Shader(const std::string &name, const char *vertexCode, const char *fragmentCode);
	~Shader();

	const std::string &GetName() const { return this->m_name; }

	void Use() const;

	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;
	void SetFloat(const std::string &name, float x, float y, float z) const;
	void SetVector(const std::string& name, Vec3 value) const;
	void SetMatrix(const std::string &name, Mat4 value) const;

private:
	GLuint m_shaderProgramID;
	std::string m_name;

	void CreateProgram(const char *vertexCode, const char *fragmentCode);
};
