#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 modelMatrix;
layout (std430, binding = 0) buffer CameraBuffer 
{
    mat4 projectionMatrix;
    mat4 viewMatrix;
    vec3 pos;
} camera;

layout (location = 0) out vec2 TexCoord;
layout (location = 1) out vec3 Normal;
layout (location = 2) out vec3 FragPos;
layout (location = 3) out vec3 CameraPos;

void main()
{
    gl_Position = camera.projectionMatrix * camera.viewMatrix * modelMatrix * vec4(aPos, 1.0);

    TexCoord = aTexCoord;
    
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    Normal = normalize(normalMatrix * aNormal);
    
    FragPos = vec3(modelMatrix * vec4(aPos, 1.0));
    CameraPos = camera.pos;
}