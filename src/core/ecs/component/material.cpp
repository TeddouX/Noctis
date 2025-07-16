#include "material.hpp"


void Material::UploadData()
{
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
        {"shader", this->m_shader->GetName()}
    END_SERIALIZATION()
}


void Material::Deserialize(const json &j)
{
    PROP_FROM_JSON(j, color)
    PROP_FROM_JSON(j, specularReflectance)
    PROP_FROM_JSON(j, specularDefinition)
    PROP_FROM_JSON(j, m_name)
    this->m_shader = AssetManager::GetInstance().GetShader(j["shader"]);
}
