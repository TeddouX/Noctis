#include "ecs/component/light_component.hpp"


DirectionalLight::Data DirectionalLight::GetData()
{
    DirectionalLight::Data data;
    data.rotation = Vec4(this->m_rotation, 0);
    data.ambient = this->m_ambient.ToPaddedFloats();
    data.diffuse = this->m_diffuse.ToPaddedFloats();
    data.specular = this->m_specular.ToPaddedFloats();
    
    return data;
}


void DirectionalLight::Serialize(json &j) const
{
    START_SERIALIZATION(j)
        PROP_TO_JSON(m_rotation),
        PROP_TO_JSON(m_ambient),
        PROP_TO_JSON(m_diffuse),
        PROP_TO_JSON(m_specular)
    END_SERIALIZATION()
}


void DirectionalLight::Deserialize(const json &j)
{
    PROP_FROM_JSON(j, m_rotation);
    PROP_FROM_JSON(j, m_ambient);
    PROP_FROM_JSON(j, m_diffuse);
    PROP_FROM_JSON(j, m_specular);
}


std::vector<std::shared_ptr<IPropertyBase>> DirectionalLight::GetProperties()
{
    return {
        std::make_shared<ColorProperty>(GETTER_FOR_REF(this->m_ambient), "Ambient Color"),
        std::make_shared<ColorProperty>(GETTER_FOR_REF(this->m_diffuse), "Diffuse Color"),
        std::make_shared<ColorProperty>(GETTER_FOR_REF(this->m_specular), "Specular Color"),
    };
}

