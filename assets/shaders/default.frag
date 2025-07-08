#version 430 core

layout (location = 0) in vec2 TexCoord;
layout (location = 1) in vec3 Normal;

layout (location = 0) out vec4 FragColor;

// uniform sampler2D Texture;

void main()
{
    // FragColor = texture(Texture, TexCoord);
    FragColor = vec4(1);
}