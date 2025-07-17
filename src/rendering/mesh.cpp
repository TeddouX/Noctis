#include "mesh.hpp"


Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures)
    : m_vertices(vertices), m_indices(indices), m_textures(textures)
{
    // Generate buffers
    glGenVertexArrays(1, &this->m_VAO);
    glGenBuffers(1,      &this->m_VBO);
    glGenBuffers(1,      &this->m_EBO);
    
    glBindVertexArray(this->m_VAO);

    // Load data into the VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
    glBufferData(
        GL_ARRAY_BUFFER, 
        vertices.size() * sizeof(Vertex), 
        vertices.data(), 
        GL_STATIC_DRAW
    );  

    // Load data into the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, 
        indices.size() * sizeof(GLuint), 
        indices.data(), 
        GL_STATIC_DRAW
    );

    // Create vertex attributes buffers
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
}


void Mesh::Render(Shader &shader)
{
    // TODO:
    // this->m_texture.Bind();

    glBindVertexArray(this->m_VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)this->m_indices.size(), GL_UNSIGNED_INT, 0);
}
