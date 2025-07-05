#include "texture.hpp"

#include <iostream>


Texture::Texture(int width, int height)
{
    glGenTextures(1, &this->m_id);
    glBindTexture(GL_TEXTURE_2D, this->m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  

    glBindTexture(GL_TEXTURE_2D, 0);
}


Texture::Texture(const std::string &path, TextureType type)
    : m_type(type)
{
	LOG_INFO("Loading texture: {}", path)

    glGenTextures(1, &this->m_id);
	glBindTexture(GL_TEXTURE_2D, this->m_id);

	// Texture "parameters"
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat on the X axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat on the Y axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Linearly interpolates between the two closest mipmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Smoother pattern where individual pixels are less visible

	// Load the image
	unsigned char* imageData = stbi_load(path.c_str(), &this->m_width, &this->m_height, &this->m_nrChannels, 0);
	
	if (imageData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_width, this->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		LOG_ERR("Failed to load image: {}", path)
	

	stbi_image_free(imageData);

	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->m_id);
}


GLuint Texture::GetID() const
{
    return this->m_id;
} 
