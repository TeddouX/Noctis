#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

layout (std430, binding = 0) buffer CameraBuffer {
    mat4 projectionMatrix;
    mat4 viewMatrix;
    mat4 modelMatrix;   
} camera;

out vec2 TexCoord;
out vec3 Normal;

void main()
{
    gl_Position = /* camera.projectionMatrix * camera.viewMatrix * camera.modelMatrix **/ vec4(aPos, 1.0);
    TexCoord = vec2(aTexCoord.x, 1 - aTexCoord.y);
    Normal = aNormal;
}