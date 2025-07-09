#include "light.hpp"
#include <iostream>


DirectionalLight::Data DirectionalLight::GetData()
{
    DirectionalLight::Data data;
    data.rotation = Vec4(this->rotation, 0);
    data.ambient = this->ambient.ToPaddedFloats();
    data.diffuse = this->diffuse.ToPaddedFloats();
    data.specular = this->specular.ToPaddedFloats();
    
    return data;
}
