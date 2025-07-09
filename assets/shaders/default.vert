#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

layout (std430, binding = 0) buffer CameraBuffer 
{
    mat4 projectionMatrix;
    mat4 viewMatrix;
    mat4 modelMatrix;
    vec3 pos;
} camera;

layout (location = 0) out vec2 TexCoord;
layout (location = 1) out vec3 Normal;
layout (location = 2) out vec3 FragPos;
layout (location = 3) out vec3 CameraPos;

void main()
{
    gl_Position = camera.projectionMatrix * camera.viewMatrix * camera.modelMatrix * vec4(aPos, 1.0);

    TexCoord = vec2(aTexCoord.x, 1 - aTexCoord.y);
    
    mat3 normalMatrix = transpose(inverse(mat3(camera.modelMatrix)));
    Normal = normalize(normalMatrix * aNormal);
    
    FragPos = vec3(camera.modelMatrix * vec4(aPos, 1.0));
    CameraPos = camera.pos;
}