#include "texture.hpp"


BasicTexture::BasicTexture(int width, int height, int internalFormat, int format)
{
	// this->Generate(false);
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


BasicTexture::BasicTexture(const fs::path &path, TextureType type)
    : m_type(type)
{
	LOG_INFO("Loading texture: {}", path.string())
	this->Generate(true);

	this->m_name = Filesystem::GetFileName(path);

	// Load the image
	unsigned char *imageData = stbi_load(
		path.string().c_str(), 
		&this->m_width, 
		&this->m_height, 
		&this->m_nrChannels, 
		0
	);
	
	if (!this->LoadFromStbi(imageData))
		LOG_ERR("Failed to load image: {}", path.string())
}


BasicTexture::BasicTexture(unsigned char *data, int width, TextureType type, std::string name)
	: m_type(type), m_name(name)
{
	this->Generate(true);

	unsigned char *imageData = stbi_load_from_memory(
    	data,
        width,
        &this->m_width, 
		&this->m_height, 
		&this->m_nrChannels, 
		0
	);

	if (!this->LoadFromStbi(imageData))
		LOG_ERR("Failed to load texture from memory")
}


BasicTexture::BasicTexture(unsigned char *data, TextureType type, std::string name)
	: m_type(type), m_name(name)
{
	this->Generate(true);

	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		GL_RGB, 
		this->m_width, 
		this->m_height, 
		0, 
		GL_RGB, 
		GL_UNSIGNED_BYTE, 
		data
	);
	glGenerateMipmap(GL_TEXTURE_2D);
}


void BasicTexture::Generate(bool mipmaps)
{
	glGenTextures(1, &this->m_id);
	glBindTexture(GL_TEXTURE_2D, this->m_id);

	LOG_INFO("{}", this->m_id)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	if (mipmaps)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
}


bool BasicTexture::LoadFromStbi(unsigned char *data)
{
	bool success = false;

	GLenum format;
	if (this->m_nrChannels == 1)
		format = GL_RED;
	else if (this->m_nrChannels == 3)
		format = GL_RGB;
	else if (this->m_nrChannels == 4)
		format = GL_RGBA;

	if (data)
	{
		glTexImage2D(
			GL_TEXTURE_2D, 
			0, 
			format, 
			this->m_width, 
			this->m_height, 
			0, 
			format, 
			GL_UNSIGNED_BYTE, 
			data
		);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	
		success = true;
	}

	// stbi_image_free(data);

	return success;
}


void BasicTexture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, this->m_id);
}


void BasicTexture::BindToPoint(int bindPoint)
{
	glActiveTexture(GL_TEXTURE0 + bindPoint);
	glBindTexture(GL_TEXTURE_2D, this->m_id);
}


void BasicTexture::Delete()
{
    glDeleteTextures(1, &this->m_id);
}


GLuint BasicTexture::GetID() const
{
    return this->m_id;
}


PBRTexture::PBRTexture(
	const std::string &name,
	std::shared_ptr<BasicTexture> diffuseMap,
	std::shared_ptr<BasicTexture> specularMap,
	std::shared_ptr<BasicTexture> normalMap,
	std::shared_ptr<BasicTexture> heightMap
) 
	: m_name(name), 
	  m_diffuseMap(diffuseMap), 
	  m_specularMap(specularMap), 
	  m_normalMap(normalMap), 
	  m_heightMap(heightMap)
{
}


void PBRTexture::Bind()
{
	if (this->m_diffuseMap)  this->m_diffuseMap->BindToPoint(0);
	if (this->m_specularMap) this->m_specularMap->BindToPoint(1);
	if (this->m_normalMap)   this->m_normalMap->BindToPoint(2);
	if (this->m_heightMap)   this->m_heightMap->BindToPoint(3);
}


void PBRTexture::Delete()
{

}
