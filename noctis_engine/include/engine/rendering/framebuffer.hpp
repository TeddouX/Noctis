#pragma once
#include <iostream>
#include <Windows.h>
#include <glad/glad.h>

#include "texture.hpp"
#include "../math/math.hpp"


class NOCTIS_API FrameBuffer
{
public:
    FrameBuffer();
    FrameBuffer(IVec2 size);
    ~FrameBuffer();

    void Init(IVec2 size);
    void Delete();

    void Bind() const;
    void Unbind() const;

    void Resize(IVec2 size);
    inline const IVec2 &GetSize() const { return this->m_size; }

    GLuint GetTextureID() const;

private:
    BasicTexture m_texture, m_depthTexture;
    IVec2  m_size;
    GLuint m_id;
};
