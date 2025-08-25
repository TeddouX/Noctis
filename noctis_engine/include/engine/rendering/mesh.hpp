#pragma once
#include <vector>
#include <glad/glad.h>

#include "vertex.hpp"
#include "texture.hpp"
#include "shader.hpp"


class NOCTIS_API Mesh
{
public:
    Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices);

    void SetTransformMatrix(Mat4 transform) { this->m_transformMatrix = transform; }

    void Render(Shader &shader, const Mat4 &modelMatrix);

private:
    GLuint  m_VAO, m_VBO, m_EBO;
    GLsizei m_indicesSize;
    Mat4    m_transformMatrix;
};
