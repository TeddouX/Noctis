#include "ecs/component/material_component.hpp"


Material::Material(const std::string& name, std::shared_ptr<Shader> shader, std::shared_ptr<ITexture> texture)
    : m_name(name), 
    m_shader(shader), 
    m_texture(texture) 
{
    if (!this->m_texture)
        this->m_texture = std::make_shared<PBRTexture>("");
};



void Material::UploadData(Shader &shader)
{
    // 0 - Colored
    // 1 - Basic Textured
    // 2 - PBR Textured
    int materialType = 0;
    if (std::dynamic_pointer_cast<BasicTexture>(this->m_texture))
        materialType = 1;
    
    auto pbr = std::dynamic_pointer_cast<PBRTexture>(this->m_texture);
    if (!pbr->IsEmpty())
        materialType = 2;

    this->m_texture->Bind();

    // Set the material type uniform
    shader.SetInt("materialType", materialType);

    // Color          + 16 bytes
    // SpecReflect    + 12 bytes
    // SpecDefinition + 4 bytes
    // Total          = 32 bytes
    // CCCCCCCCCCCC----
    // RRRRRRRRRRRRDDDD
    Material::Data data {
        this->m_color.ToPaddedFloats(),
        this->m_specularReflectance.ToFloats(),
        this->m_specularDefinition
    };

    this->m_ssbo.UploadData(data);
}


void Material::Serialize(json &j) const
{
    START_SERIALIZATION(j)
        COMPONENT_TO_JSON(Material),
        PROP_TO_JSON(m_color),
        PROP_TO_JSON(m_specularReflectance),
        PROP_TO_JSON(m_specularDefinition),
        PROP_TO_JSON(m_name),
        {"shader", this->m_shader->GetName()},
        {
            "texture", 
            this->m_texture->IsEmpty()
            ? json(nullptr)        
            : json(this->m_texture->GetName())
        }
    END_SERIALIZATION()
}


void Material::Deserialize(const json &j)
{
    PROP_FROM_JSON(j, m_color)
    PROP_FROM_JSON(j, m_specularReflectance)
    PROP_FROM_JSON(j, m_specularDefinition)
    PROP_FROM_JSON(j, m_name)

    this->m_shader = AssetManager::GetInstance().GetShader(j["shader"]);

    if (!j["texture"].is_null())
        this->m_texture = AssetManager::GetInstance().GetTexture(j["texture"]);
    else
        // A PBR texture in wich every texture 
        // is a 1x1 white pixel
        this->m_texture = std::make_shared<PBRTexture>("");
}


std::vector<std::shared_ptr<IPropertyBase>> Material::GetProperties()
{
    return {
        std::make_shared<ShaderProperty>(GETTER_FOR(*this->m_shader), "Shader"),
        std::make_shared<ColorProperty>(GETTER_FOR(this->m_color), "Color"),
        std::make_shared<ColorProperty>(GETTER_FOR(this->m_specularReflectance), "Specular Reflectance"),
        std::make_shared<FloatProperty>(GETTER_FOR(this->m_specularDefinition), "Specular Definittion", 0.f, 100.f),
    };
}
