#pragma once
#include <string>
#include <glad/glad.h>
#include <stb_image.h>

#include "../logger.hpp"
#include "../math/math.hpp"
#include "../filesystem.hpp"


enum class NOCTIS_API TextureType
{
    INVALID,
    DIFFUSE,
    SPECULAR,
    NORMAL,
    HEIGHT
};


class NOCTIS_API ITexture
{
public:
    virtual ~ITexture() {}; 
    virtual void Bind() = 0;
    virtual void Delete() = 0;
    virtual bool IsEmpty() const = 0;
    virtual const std::string &GetName() const = 0; 
};


class NOCTIS_API BasicTexture : public ITexture
{
public:
    BasicTexture() = default;

    /// @brief Create an empty texture of size
    BasicTexture(int width, int height, int internalFormat = GL_RGB, int format = GL_RGB);

    /// @brief Load from image path
    BasicTexture(const fs::path &path, TextureType type);

    /// @brief Load compressed data from memory
    BasicTexture(uint8_t *data, int width, TextureType type, std::string name);

    /// @brief Load raw data from memory
    BasicTexture(uint8_t *data, IVec2 size, TextureType type, std::string name);

    /// @returns A 1x1 white texture 
    static std::shared_ptr<BasicTexture> Get1x1WTex(TextureType type);

    GLuint GetID() const;
    const std::string &GetName() const override { return this->m_name; }
    TextureType        GetTexType() const { return this->m_type; }

    void Bind() override;
    void BindToPoint(int bindPoint) const;
    void Delete() override;

    bool IsEmpty() const override { return this->m_name == emptyTexName; }

private:
    // Stands for 1x1 White Texture
    inline static std::string emptyTexName = "1x1WTex";

    TextureType m_type = TextureType::INVALID;
    std::string m_name;
    GLuint      m_id;

    int m_width, m_height; 
    int m_nrChannels;

    void Generate(bool mipmaps);
    bool LoadFromStbi(unsigned char *data);
};



class NOCTIS_API PBRTexture : public ITexture
{
public:
    PBRTexture(
        const std::string &name,
        std::shared_ptr<BasicTexture> diffuseMap = nullptr,
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

    bool IsEmpty() const override;

    const std::string &GetName() const override { return this->m_name; }

private:
    std::string m_name;
    std::shared_ptr<BasicTexture> m_diffuseMap;
    std::shared_ptr<BasicTexture> m_specularMap;
    std::shared_ptr<BasicTexture> m_normalMap;
    std::shared_ptr<BasicTexture> m_heightMap;  
};
