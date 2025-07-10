#pragma once
#include <string>
#include <memory>

#include "component.hpp"
#include "../../../rendering/shader.hpp"
#include "../../../rendering/ssbo.hpp"
#include "../../math/math.hpp"
#include "../../math/color.hpp"


class Material : public IComponent
{
public:
    ENABLE_REFLECTION(Material)

    struct Data
    {
        Vec4 diffuseReflectance;
        Vec3 specularReflectance;
        float shininess;
    };

    PROPERTY_D(Color, color, Color(179, 175, 174))
    PROPERTY_D(Color, specularReflectance, Color::White())
    PROPERTY_D(float, specularDefinition, 32.f)

    Material() = default;
    Material(const std::string &name, std::shared_ptr<Shader> shader)
        : m_name(name), m_shader(shader) {};

    inline std::string &GetName() { return this->m_name; }
    PROPERTY_GETTER(GetName)
    
    inline std::shared_ptr<Shader> &GetShader() { return this->m_shader; }
    PROPERTY_GETTER(GetShader)

    void UploadData();

private:
    SSBO<Material::Data>    m_ssbo = SSBO<Material::Data>(1);
    std::string             m_name;
    std::shared_ptr<Shader> m_shader;
};
