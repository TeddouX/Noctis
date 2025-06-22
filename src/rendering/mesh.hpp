#pragma once
#include <vector>
#include <glad/glad.h>

#include "vertex.hpp"
#include "texture.hpp"
#include "shader.hpp"


class Mesh
{
public:
    Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &texture);

    void Render(Shader &shader);

private:
    GLuint m_VAO, m_VBO, m_EBO;

    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;
    std::vector<Texture> m_textures;
};
