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
    vec3 diffuse;
    vec3 specular;
    float shininess;
} material;

layout (std430, binding = 2) buffer DirectionalLights
{
    uint dirLightCount;
    DirectionalLight dirLights[];
};


vec3 DirectionalLighting(DirectionalLight light)
{
    float ambientStrength = 0.1; // ?

    // Ambient
    vec3 ambient = light.ambient * material.diffuse * ambientStrength;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * material.diffuse * diff;  
    
    // Specular
    vec3 viewDir = normalize(CameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * material.specular;

    return ambient + diffuse + specular;
}


void main()
{
    vec3 final = vec3(0);

    for (int i = 0; i < dirLightCount; i++)
    {
        final += DirectionalLighting(dirLights[i]);
    }

    FragColor = vec4(final, 1.0);
}
