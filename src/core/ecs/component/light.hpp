#pragma once
#include "component.hpp"
#include "../../math/color.hpp"


class DirectionalLight : public IComponent
{
public:
    ENABLE_REFLECTION(DirectionalLight)
    
    struct Data
    {
        Vec4 rotation;
        Vec4 ambient;
        Vec4 diffuse;
        Vec4 specular;
    };

    // The rotation doesn't need to be displayed in the editor
    Vec3 rotation; 
    PROPERTY_D(Color, ambient, Color::White())
    PROPERTY_D(Color, diffuse, Color::White())
    PROPERTY_D(Color, specular, Color::White())

    DirectionalLight() = default;
    DirectionalLight(Color ambient, Color diffuse, Color specular)
        : ambient(ambient), diffuse(diffuse), specular(specular) {};

    Data GetData();
};
