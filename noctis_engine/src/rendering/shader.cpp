#include "rendering/shader.hpp"


static bool CheckUniform(int location, const std::string& uniformName)
{
	if (location == -1)
	{
		LOG_WARN("Uniform {} couldn't be found.", uniformName);
        return false;
	}

    return true;
}


Shader::Shader(const fs::path &vertexPath, const fs::path &fragmentPath)
{
	LOG_INFO("Loading shaders: {}, {}", vertexPath, fragmentPath);

	std::string vertexString = Filesystem::GetFileContents(vertexPath);
	std::string fragmentString = Filesystem::GetFileContents(fragmentPath);
	
	if (vertexString.empty() || fragmentString.empty())
		return;

	this->CreateProgram(vertexString.c_str(), fragmentString.c_str());
}


Shader::Shader(const fs::path &shaderPath)
{
	LOG_INFO("Loading shader: {}, {}", shaderPath);

	std::string shaderString = Filesystem::GetFileContents(shaderPath);
	
	if (shaderPath.empty())
		return;

	std::string vertexString = std::string(NOCTIS_OPENGL_VERSION) + "\n#define VERTEX\n" + shaderString;
	std::string fragmentString = std::string(NOCTIS_OPENGL_VERSION) + "\n#define FRAGMENT\n" + shaderString;

	this->CreateProgram(vertexString.c_str(), fragmentString.c_str());
}


void Shader::CreateProgram(const char *vertexCode, const char *fragmentCode)
{
	int success;
	char infoLog[1024];

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);

		LOG_ERR("Vertex shader compilation failed:\n{}", infoLog);
	}


	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);

		LOG_ERR("Fragment shader compilation failed:\n{}", infoLog);
	}


	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	
	if (!success)
	{
		glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
		LOG_ERR("Shader program linking error:\n{}", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	this->m_shaderProgramID = program;
}



void Shader::Use() const
{
	glUseProgram(this->m_shaderProgramID);

	GLenum err = glGetError();
	if (err != GL_NO_ERROR) 
		LOG_ERR("glUseProgram failed: {:#x}", err);
}


void Shader::SetBool(const std::string &name, bool value) const
{
	int location = glGetUniformLocation(this->m_shaderProgramID, name.c_str());
	if (!CheckUniform(location, name)) return;
	glUniform1i(location, value);
}

void Shader::SetInt(const std::string& name, int value) const
{
	int location = glGetUniformLocation(this->m_shaderProgramID, name.c_str());
	if (!CheckUniform(location, name)) return;
	glUniform1i(location, value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	int location = glGetUniformLocation(this->m_shaderProgramID, name.c_str());
	if (!CheckUniform(location, name)) return;
	glUniform1f(location, value);
}

void Shader::SetFloat(const std::string& name, float x, float y, float z) const
{
	int location = glGetUniformLocation(this->m_shaderProgramID, name.c_str());
	if (!CheckUniform(location, name)) return;
	glUniform3f(location, x, y, z);
}

void Shader::SetVector(const std::string& name, Vec3 value) const
{
	int location = glGetUniformLocation(this->m_shaderProgramID, name.c_str());
	if (!CheckUniform(location, name)) return;
	glUniform3fv(location, 1, &value[0]);
}

void Shader::SetMatrix(const std::string& name, Mat4 value) const
{
	int location = glGetUniformLocation(this->m_shaderProgramID, name.c_str());
    if (!CheckUniform(location, name)) return;
	glUniformMatrix4fv(location, 1, GL_FALSE, GetPtr(value));
}
