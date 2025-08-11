#pragma once
#include "component.hpp"
#include "property/color_property.hpp"
#include "../../math/color.hpp"


class NOCTIS_API DirectionalLight : public IComponent
{
public:
    REGISTER_COMPONENT(DirectionalLight, "Directional Light")

    struct Data
    {
        Vec4 rotation;
        Vec4 ambient;
        Vec4 diffuse;
        Vec4 specular;
    };

    DirectionalLight() = default;
    DirectionalLight(Color ambient, Color diffuse, Color specular)
        : m_ambient(ambient), m_diffuse(diffuse), m_specular(specular) {};

    Data GetData();

    void SetRotation(const Vec3 &rot) { this->m_rotation = rot; }

    void Serialize(json &j) const override;
    void Deserialize(const json &j) override;

    std::vector<std::shared_ptr<IPropertyBase>> GetProperties() override;

private:
    Vec3 m_rotation = Vec3(0);
    Color m_ambient = Color::White();
    Color m_diffuse = Color::White();
    Color m_specular = Color::White();
};
