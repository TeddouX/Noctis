#pragma once
#include <string>
#include <glad/glad.h>
#include <stb_image.h>

#include "../core/logger.hpp"


enum TextureType
{
    DIFFUSE,
    SPECULAR,
    NORMAL,
    HEIGHT
};


class Texture
{
public:
    Texture(int width, int height, int internalFormat = GL_RGB, int format = GL_RGB);
    Texture(const std::string &path, TextureType type);


    GLuint GetID() const;

    void Bind() const;
    void Delete();

private:
    GLuint      m_id;
    TextureType m_type;

    int m_width, m_height; 
    int m_nrChannels;
};
