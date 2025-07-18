#pragma once
#include <vector>
#include <glad/glad.h>

#include "vertex.hpp"
#include "texture.hpp"
#include "shader.hpp"


class Mesh
{
public:
    Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::shared_ptr<ITexture> texture);
    ~Mesh();

    void Render(Shader &shader);

private:
    GLuint m_VAO, m_VBO, m_EBO;

    std::shared_ptr<ITexture> m_texture;
    std::vector<Vertex>  m_vertices;
    std::vector<GLuint>  m_indices;
};
