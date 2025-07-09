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
    PROPERTY(Color, ambient)
    PROPERTY(Color, diffuse)
    PROPERTY(Color, specular)

    DirectionalLight()
        : ambient(Color::White()), diffuse(Color::White()), specular(Color::White()) {};
    
    DirectionalLight(Color ambient, Color diffuse, Color specular)
        : ambient(ambient), diffuse(diffuse), specular(specular) {};

    Data GetData();
};
