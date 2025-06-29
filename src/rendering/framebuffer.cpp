#include "framebuffer.hpp"


FrameBuffer::FrameBuffer(int width, int height)
    : m_texture(width, height)
{
    this->Init(width, height);
}


void FrameBuffer::Init(int width, int height)
{
    this->width = width;
    this->height = height;
    this->m_texture = Texture(width, height);

    glGenFramebuffers(1, &this->m_id);
    glBindFramebuffer(GL_FRAMEBUFFER, this->m_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_texture.GetID(), 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void FrameBuffer::Delete()
{
    glDeleteFramebuffers(1, &this->m_id);

    GLuint textureID = this->m_texture.GetID();
    glDeleteTextures(1, &textureID);
}


void FrameBuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_id);
}


void FrameBuffer::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void FrameBuffer::Resize(int width, int height)
{
    this->Delete();
    this->Init(width, height);
}


GLuint FrameBuffer::GetTextureID() const
{
    return this->m_texture.GetID();
}
