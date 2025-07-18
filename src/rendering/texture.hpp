#pragma once
#include <string>
#include <glad/glad.h>
#include <stb_image.h>

#include "../core/logger.hpp"
#include "../core/filesystem.hpp"


enum class TextureType
{
    INVALID,
    DIFFUSE,
    SPECULAR,
    NORMAL,
    HEIGHT
};


class ITexture
{
public:
    virtual ~ITexture() {}; 
    virtual void Bind() = 0;
    virtual void Delete() = 0;
};


class BasicTexture : public ITexture
{
public:
    /// @brief Create an empty texture of size
    BasicTexture(int width, int height, int internalFormat = GL_RGB, int format = GL_RGB);

    /// @brief Load from image path
    BasicTexture(const fs::path &path, TextureType type);

    /// @brief Load compressed data from memory
    BasicTexture(unsigned char *data, int width, TextureType type, std::string name);

    /// @brief Load raw data from memory
    BasicTexture(unsigned char *data, TextureType type, std::string name);

    GLuint GetID() const;
    inline TextureType GetTexType() const { return this->m_type; }

    void Bind() override;
    void BindToPoint(int bindPoint);
    void Delete() override;

private:
    GLuint      m_id;
    TextureType m_type;
    std::string m_name;

    int m_width, m_height; 
    int m_nrChannels;

    void Generate();
    bool LoadFromStbi(unsigned char *data);
};



class PBRTexture : public ITexture
{
public:
    PBRTexture(
        std::shared_ptr<BasicTexture> diffuseMap,
        std::shared_ptr<BasicTexture> specularMap = nullptr,
        std::shared_ptr<BasicTexture> normalMap = nullptr,
        std::shared_ptr<BasicTexture> heightMap = nullptr
    );

    // Diffuse  - Texture0
    // Specular - Texture1
    // Normal   - Texture2
    // Height   - Texture3
    void Bind() override;
    void Delete() override;

private:
    std::shared_ptr<BasicTexture> m_diffuseMap;
    std::shared_ptr<BasicTexture> m_specularMap;
    std::shared_ptr<BasicTexture> m_normalMap;
    std::shared_ptr<BasicTexture> m_heightMap;  
};
