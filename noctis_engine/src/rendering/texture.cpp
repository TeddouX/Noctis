#include "rendering/texture.hpp"


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
	LOG_INFO("Loading texture: {}", path.string());
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
		LOG_ERR("Failed to load image: {}", path.string());
}


BasicTexture::BasicTexture(uint8_t *data, int width, TextureType type, std::string name)
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
		LOG_ERR("Failed to load texture from memory");
}


BasicTexture::BasicTexture(uint8_t *data, IVec2 size, TextureType type, std::string name)
	: m_type(type), m_name(name)
{
	this->Generate(true);

	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		GL_RGB, 
		size.x, 
		size.y, 
		0, 
		GL_RGB, 
		GL_UNSIGNED_BYTE, 
		data
	);
	glGenerateMipmap(GL_TEXTURE_2D);
}


std::shared_ptr<BasicTexture> BasicTexture::Get1x1WTex(TextureType type)
{
	static auto tex = std::make_shared<BasicTexture>(
		new uint8_t[3]{ 255, 255, 255 },
		IVec2(1),
		type,
		emptyTexName
	);
	
	return tex;
}


void BasicTexture::Generate(bool mipmaps)
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


bool BasicTexture::LoadFromStbi(unsigned char *data)
{
	bool success = false;

	GLenum format = GL_RGBA;
	if (this->m_nrChannels == 1)
		format = GL_RED;
	else if (this->m_nrChannels == 3)
		format = GL_RGB;

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


void BasicTexture::BindToPoint(int bindPoint) const
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
	  m_diffuseMap(diffuseMap ? diffuseMap : BasicTexture::Get1x1WTex(TextureType::DIFFUSE)),
	  m_specularMap(specularMap ? specularMap : BasicTexture::Get1x1WTex(TextureType::SPECULAR)),
	  m_normalMap(normalMap ? normalMap : BasicTexture::Get1x1WTex(TextureType::NORMAL)),
	  m_heightMap(heightMap ? heightMap : BasicTexture::Get1x1WTex(TextureType::HEIGHT))
{
}


void PBRTexture::Bind()
{
	this->m_diffuseMap->BindToPoint(0);
	this->m_specularMap->BindToPoint(1);
	this->m_normalMap->BindToPoint(2);
	this->m_heightMap->BindToPoint(3);
}


void PBRTexture::Delete()
{
	this->m_diffuseMap->Delete();
	this->m_specularMap->Delete();
	this->m_normalMap->Delete();
	this->m_heightMap->Delete();
}


bool PBRTexture::IsEmpty() const
{
	return this->m_diffuseMap->IsEmpty()
		&& this->m_specularMap->IsEmpty()
		&& this->m_normalMap->IsEmpty()
		&& this->m_heightMap->IsEmpty();
}
