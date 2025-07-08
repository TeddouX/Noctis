#version 430 core

layout (location = 0) in vec2 TexCoord;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec3 FragPos;
layout (location = 3) in vec3 CameraPos;

layout (location = 0) out vec4 FragColor;

struct DirectionalLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

layout (std430, binding = 1) buffer ColoredMaterial
{
    vec3 ambientReflectance;
    vec3 diffuseReflectance; // Color
    vec3 specularReflectance; // Color
} material;


void main()
{

}


vec3 DirectionalLighting(DirectionalLight light)
{
    float specularSize = 32;

    // Ambient
    vec3 ambient = material.ambientReflectance * light.ambient;

    // Diffuse
    vec3 lightDirection = normalize(-light.direction);
    float difference = max(0, dot(lightDirection, Normal));
    vec3 diffuse = material.diffuseReflectance * light.diffuse * difference;

    // Specular (Blinn Phong)
    vec3 viewDir = normalize(CameraPos - FragPos);
    vec3 halfwayDir = normalize(lightDirection + CameraPos);
    float spec = pow(max(dot(Normal, halfwayDir), 0), specularSize);
    vec3 specular = material.specularReflectance * light.specular * spec;

    return ambient + diffuse + specular;
}
