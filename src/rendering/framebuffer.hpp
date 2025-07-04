#pragma once
#include <iostream>
#include <Windows.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.hpp"


class FrameBuffer
{
public:

    FrameBuffer();
    FrameBuffer(glm::ivec2 size);
    
    void Init(glm::ivec2 size);
    void Delete();

    void Bind() const;
    void Unbind() const;

    void Resize(glm::ivec2 size);
    inline const glm::ivec2 &GetSize() const { return this->m_size; }

    GLuint GetTextureID() const;

private:
    glm::ivec2 m_size;
    GLuint    m_id;
    Texture   m_texture;
};
