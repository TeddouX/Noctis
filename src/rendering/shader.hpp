#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


#include "../core/logger.hpp"


static bool CheckUniform(int location, const std::string &uniformName);


class Shader
{
public:
	Shader(const std::string &vertexPath, const std::string &fragmentPath);
	~Shader();

	void Use() const;

	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;
	void SetFloat(const std::string &name, float x, float y, float z) const;
	void SetVector(const std::string& name, glm::vec3 value) const;
	void SetMatrix(const std::string &name, glm::mat4 value) const;

private:
	GLuint m_shaderProgramID;
};
