#include <rendering/opengl/ogl_shader.hpp>
#include <glad/glad.h>
#include <iostream>

namespace Noctis
{
    
ShaderOpenGL::ShaderOpenGL(const char *vertCode, const char *fragCode) {
    int success;
    char infolog[1024];
    
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertCode, nullptr);
    glCompileShader(vertShader);
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertShader, sizeof(infolog), nullptr, infolog);
        std::cerr << "Vertex shader compilation failed: " << infolog << std::endl;
    }

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragCode, nullptr);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragShader, sizeof(infolog), nullptr, infolog);
        std::cerr << "Fragment shader compilation failed: " << infolog << std::endl;
    }

    programID_ = glCreateProgram();
    glAttachShader(programID_, vertShader);
    glAttachShader(programID_, fragShader);
    glLinkProgram(programID_);
    glGetProgramiv(programID_, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(programID_, sizeof(infolog), nullptr, infolog);
        std::cerr << "Program linking failed: " << infolog << std::endl;
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

void ShaderOpenGL::setUBO(const UniformBufferOpenGL &ubo, const char *uniformName) {
    uint32_t blockIndex = glGetUniformBlockIndex(programID_, uniformName);

    if (blockIndex < 0) {
        std::cerr << "Uniform " << uniformName << " couldn't be found" << std::endl;
        return;
    }

    glUniformBlockBinding(programID_, blockIndex, ubo.getBindPoint());
}

void ShaderOpenGL::bind() {
    glUseProgram(programID_);
}

void ShaderOpenGL::setUniform(const UniformInfo &info) {
    int loc = glGetUniformLocation(programID_, info.name.c_str());
    
    if (loc < 0) {
        std::cerr << "Uniform " << info.name << " couldn't be found" << std::endl;
        return;
    }

    switch (info.type) {
        case UniformType::BOOL:  glUniform1i(loc, std::get<bool>(info.val));
        case UniformType::INT:   glUniform1i(loc, std::get<int>(info.val));
        case UniformType::FLOAT: glUniform1f(loc, std::get<float>(info.val));
    }
}

} // namespace Noctis

