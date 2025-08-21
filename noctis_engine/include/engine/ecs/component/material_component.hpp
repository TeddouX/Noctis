#pragma once
#include <string>
#include <memory>

#include "component.hpp"
#include "property/color_property.hpp"
#include "property/float_property.hpp"
#include "property/shader_property.hpp"
#include "../../asset/asset_manager.hpp"
#include "../../math/math.hpp"
#include "../../math/color.hpp"
#include "../../rendering/texture.hpp"
#include "../../rendering/shader.hpp"
#include "../../rendering/ssbo.hpp"


class NOCTIS_API Material : public IComponent
{
public:
    REGISTER_COMPONENT(Material, "Material")

    struct Data
    {
        Vec4 diffuseReflectance;
        Vec3 specularReflectance;
        float shininess;
    };

    Material() = default;
    Material(const std::string& name, std::shared_ptr<Shader> shader, std::shared_ptr<ITexture> texture = nullptr);

    inline std::string &GetName() { return this->m_name; }
    
    inline std::shared_ptr<Shader> &GetShader() { return this->m_shader; }

    void UploadData(Shader &shader);

    void Serialize(json &j) const override;
    void Deserialize(const json &j) override;

    std::vector<std::shared_ptr<IPropertyBase>> GetProperties() override;

private:
    Color m_color = Color(179, 175, 174);
    Color m_specularReflectance = Color::White();
    float m_specularDefinition = 32.f;

    std::shared_ptr<ITexture> m_texture = std::make_shared<PBRTexture>("");
    std::shared_ptr<Shader>   m_shader = AssetManager::GetInstance().GetShader(std::string(LIT_SHADER_NAME));
    SSBO<Material::Data>      m_ssbo = SSBO<Material::Data>(1);
    std::string               m_name;
};
