#pragma once
#include <string>
#include <glad/glad.h>
#include <stb_image.h>


enum TextureType
{
    DIFFUSE, // Only one that is currently supported
    SPECULAR,
    NORMAL,
    HEIGHT
};


class Texture
{
public:
    Texture(int width, int height);
    Texture(const std::string &path, TextureType type);

    GLuint GetID() const;

    void Bind() const;

private:
    GLuint m_id;
    TextureType m_type;

    int m_width, m_height; 
    int m_nrChannels;
};
