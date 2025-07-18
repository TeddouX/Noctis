#pragma once
#include <vector>
#include <glad/glad.h>

#include "vertex.hpp"
#include "texture.hpp"
#include "shader.hpp"


class Mesh
{
public:
    Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices);

    void SetTransformMatrix(Mat4 transform) { this->m_transformMatrix = transform; }

    void Render(Shader &shader, const Mat4 &modelMatrix);

private:
    GLuint m_VAO, m_VBO, m_EBO;

    std::vector<Vertex>  m_vertices;
    std::vector<GLuint>  m_indices;
    Mat4                 m_transformMatrix;
};
