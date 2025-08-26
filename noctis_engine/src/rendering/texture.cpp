#include "rendering/texture.hpp"

namespace Noctis
{

Texture::Texture(int width, int height, int internalFormat, int format)
{
	glGenTextures(1, &this->m_id);
    glBindTexture(GL_TEXTURE_2D, this->m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

    glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		internalFormat, 
		width, 
		height, 
		0, 
		format, 
		GL_UNSIGNED_BYTE, 
		nullptr
	);
}


Texture::Texture(uint8_t *data, IVec2 size, int nrChannels)
{
	this->Generate(true);

	GLenum internalFormat = GL_RGBA8;
    GLenum dataFormat = GL_RGBA;

    if (nrChannels == 1)
    {
        internalFormat = GL_R8;
        dataFormat = GL_RED;
    }
    else if (nrChannels == 3)
    {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }

	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		internalFormat, 
		size.x, 
		size.y, 
		0, 
		dataFormat,
		GL_UNSIGNED_BYTE, 
		data
	);
	glGenerateMipmap(GL_TEXTURE_2D);
}


std::shared_ptr<Texture> Texture::Get1x1WTex()
{
	static auto tex = std::make_shared<Texture>(
		new uint8_t[3]{ 255, 255, 255 },
		IVec2(1)
	);

	tex->m_empty = true;
	
	return tex;
}


void Texture::Generate(bool mipmaps)
{
	glGenTextures(1, &this->m_id);
	glBindTexture(GL_TEXTURE_2D, this->m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	if (mipmaps)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
}


void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, this->m_id);
}


void Texture::BindToPoint(int bindPoint) const
{
	glActiveTexture(GL_TEXTURE0 + bindPoint);
	glBindTexture(GL_TEXTURE_2D, this->m_id);
}


void Texture::Delete()
{
    glDeleteTextures(1, &this->m_id);
}


GLuint Texture::GetID() const
{
    return this->m_id;
}

}
