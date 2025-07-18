#version 430 core

layout (location = 0) in vec2 TexCoord;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec3 FragPos;
layout (location = 3) in vec3 CameraPos;

layout (location = 0) out vec4 FragColor;


// 0 - Colored
// 1 - Basic Textured
// 2 - PBR Textured
uniform int materialType;
layout (binding = 0) uniform sampler2D diffuseMap;
layout (binding = 1) uniform sampler2D specularMap;

layout (std430, binding = 1) buffer ColoredMaterial
{
    vec3 diffuse;
    vec3 specular;
    float shininess;
} material;


struct DirectionalLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

layout (std430, binding = 2) buffer DirectionalLights
{
    uint dirLightCount;
    DirectionalLight dirLights[];
};


vec3 GetDiffuse()
{
    if (materialType == 0 || materialType == 2)
        return material.diffuse;
    else if (materialType == 1)
        return vec3(texture(diffuseMap, TexCoord));
    else
        return vec3(255, 0, 255);
}


vec3 GetSpecular()
{
    if (materialType == 0 || materialType == 2)
        return material.specular;
    else if (materialType == 1)
    {
        return vec3(texture(specularMap, TexCoord));
    }
    else
        return vec3(255, 0, 255);
}


vec3 DirectionalLighting(DirectionalLight light)
{
    float ambientStrength = 0.1; // ?

    // Ambient
    vec3 ambient = light.ambient * GetDiffuse() * ambientStrength;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * GetDiffuse() * diff;  
    
    // Specular
    vec3 viewDir = normalize(CameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * GetSpecular();

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
