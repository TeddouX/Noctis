#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../core/math/math.hpp"
#include "../core/logger.hpp"
#include "../core/filesystem.hpp"


static bool CheckUniform(int location, const std::string &uniformName);


class Shader
{
public:
	Shader() = default;
	Shader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath);
	~Shader();

	const std::string &GetName() const { return this->m_name; }

	void Use() const;

	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;
	void SetFloat(const std::string &name, float x, float y, float z) const;
	void SetVector(const std::string &name, Vec3 value) const;
	void SetMatrix(const std::string &name, Mat4 value) const;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Shader, m_name)

private:
	GLuint m_shaderProgramID;
	std::string m_name;
	std::string m_vrPath, m_frPath;

	void CreateProgram(const char *vertexCode, const char *fragmentCode);
};
