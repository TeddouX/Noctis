#pragma once
#include <iostream>
#include <Windows.h>
#include <glad/glad.h>

#include "texture.hpp"


class FrameBuffer
{
public:
    int width, height;

    FrameBuffer(int width, int height);
    
    void Init(int width, int height);
    void Delete();

    void Bind() const;
    void Unbind() const;

    void Resize(int width, int height);

    GLuint GetTextureID() const;

private:
    GLuint  m_id;
    Texture m_texture;
};
