#version 430 core

layout (std430, binding = 1) buffer TestBuffer {
    float testFloat;
} test;

in vec2 TexCoord;

out vec4 FragColor;

// uniform sampler2D Texture;

void main()
{
    // FragColor = texture(Texture, TexCoord);
    FragColor = vec4(test.testFloat);
}