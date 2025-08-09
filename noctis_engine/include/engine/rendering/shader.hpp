#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../math/math.hpp"
#include "../logger.hpp"
#include "../filesystem.hpp"


static bool CheckUniform(int location, const std::string &uniformName);


class NOCTIS_API Shader
{
public:
	Shader() = default;
	Shader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath);
	~Shader() = default;

	const std::string &GetName() const { return this->m_name; }

	void Use() const;

	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;
	void SetFloat(const std::string &name, float x, float y, float z) const;
	void SetVector(const std::string &name, Vec3 value) const;
	void SetMatrix(const std::string &name, Mat4 value) const;

private:
	GLuint m_shaderProgramID = 0;
	std::string m_name;
	std::string m_vrPath, m_frPath;

	void CreateProgram(const char *vertexCode, const char *fragmentCode);
};
