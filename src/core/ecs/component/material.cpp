#include "material.hpp"


void Material::UploadData(Shader &shader)
{
    // 0 - Colored
    // 1 - Basic Textured
    // 2 - PBR Textured
    int materialType = 0;
    if (this->m_texture)
    {
        if (std::dynamic_pointer_cast<BasicTexture>(this->m_texture))
            materialType = 1;
        if (std::dynamic_pointer_cast<PBRTexture>(this->m_texture))
            materialType = 2;

        this->m_texture->Bind();
    }

    // Set the material type uniform
    shader.SetInt("materialType", 1);

    // Color          + 16 bytes
    // SpecReflect    + 12 bytes
    // SpecDefinition + 4 bytes
    // Total          = 32 bytes
    // CCCCCCCCCCCC----
    // RRRRRRRRRRRRDDDD
    Material::Data data {
        this->color.ToPaddedFloats(),
        this->specularReflectance.ToFloats(),
        this->specularDefinition
    };
    
    this->m_ssbo.UploadData(data);
}


void Material::Serialize(json &j) const
{
    START_SERIALIZATION(j)
        COMPONENT_TO_JSON(Material),
        PROP_TO_JSON(color),
        PROP_TO_JSON(specularReflectance),
        PROP_TO_JSON(specularDefinition),
        PROP_TO_JSON(m_name),
        {"shader", this->m_shader->GetName()},
        {"texture", this->m_texture->GetName()}
    END_SERIALIZATION()
}


void Material::Deserialize(const json &j)
{
    PROP_FROM_JSON(j, color)
    PROP_FROM_JSON(j, specularReflectance)
    PROP_FROM_JSON(j, specularDefinition)
    PROP_FROM_JSON(j, m_name)
    this->m_shader = AssetManager::GetInstance().GetShader(j["shader"]);
    this->m_texture = AssetManager::GetInstance().GetTexture(j["texture"]);
}
