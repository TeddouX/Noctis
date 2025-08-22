#pragma once
#include <string>
#include <glad/glad.h>
#include <stb_image.h>

#include "../logger.hpp"
#include "../math/math.hpp"
#include "../filesystem.hpp"


class NOCTIS_API Texture
{
public:
    Texture() = default;

    /// @brief Create an empty texture of size
    Texture(int width, int height, int internalFormat = GL_RGB, int format = GL_RGB);

    /// @brief Load raw data from memory
    Texture(uint8_t *data, IVec2 size, int nrChannels = 3);

    /// @returns A 1x1 white texture 
    static std::shared_ptr<Texture> Get1x1WTex();

    GLuint GetID() const;

    bool IsEmpty() { return this->m_empty; }

    void Bind();
    void BindToPoint(int bindPoint) const;
    void Delete();

private:
    GLuint m_id;

    bool m_empty = false;
    int m_width, m_height; 
    int m_nrChannels;

    void Generate(bool mipmaps);
};
