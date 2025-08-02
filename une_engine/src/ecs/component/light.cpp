#include "ecs/component/light.hpp"


DirectionalLight::Data DirectionalLight::GetData()
{
    DirectionalLight::Data data;
    data.rotation = Vec4(this->rotation, 0);
    data.ambient = this->ambient.ToPaddedFloats();
    data.diffuse = this->diffuse.ToPaddedFloats();
    data.specular = this->specular.ToPaddedFloats();
    
    return data;
}


void DirectionalLight::Serialize(json &j) const
{
    START_SERIALIZATION(j)
        COMPONENT_TO_JSON(DirectionalLight),
        PROP_TO_JSON(rotation),
        PROP_TO_JSON(ambient),
        PROP_TO_JSON(diffuse),
        PROP_TO_JSON(specular)
    END_SERIALIZATION()
}


void DirectionalLight::Deserialize(const json &j)
{
    PROP_FROM_JSON(j, rotation);
    PROP_FROM_JSON(j, ambient);
    PROP_FROM_JSON(j, diffuse);
    PROP_FROM_JSON(j, specular);
}
