#include "framebuffer.hpp"


FrameBuffer::FrameBuffer()
    : m_texture(0, 0)
{
    this->Init(glm::ivec2(0));
}


FrameBuffer::FrameBuffer(glm::ivec2 size)
    : m_texture(size.x, size.y)
{
    this->Init(size);
}


void FrameBuffer::Init(glm::ivec2 size)
{
    this->m_size = size;
    this->m_texture = Texture(size.x, size.y);

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


void FrameBuffer::Resize(glm::ivec2 size)
{
    this->Delete();
    this->Init(size);
}


GLuint FrameBuffer::GetTextureID() const
{
    return this->m_texture.GetID();
}
