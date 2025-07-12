#pragma once
#include "component.hpp"
#include "../../math/color.hpp"


class DirectionalLight : public IComponent, public ISerializable
{
public:
    ENABLE_REFLECTION(DirectionalLight)

    // This is the data that will be sent to the GPU for rendering
    // 16 bytes aligned for std430 compliance
    struct Data
    {
        Vec4 rotation;
        Vec4 ambient;
        Vec4 diffuse;
        Vec4 specular;
    };

    // As rotation is controlled by the light's transform, 
    // it doesn't need to be rendered in the editor
    PROPERTY_HIDDEN(Vec3, rotation, Vec3(0))
    PROPERTY_D(Color, ambient, Color::White())
    PROPERTY_D(Color, diffuse, Color::White())
    PROPERTY_D(Color, specular, Color::White())

    DirectionalLight() = default;
    DirectionalLight(Color ambient, Color diffuse, Color specular)
        : ambient(ambient), diffuse(diffuse), specular(specular) {};

    Data GetData();

    void Serialize(json &j) const override;
    void Deserialize(const json &j) override;
};
