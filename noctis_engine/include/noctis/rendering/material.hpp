#pragma once
#include "../math/color.hpp"
#include "../asset/asset.hpp"
#include "texture.hpp"

namespace Noctis
{

class Material
{
public:
    Material() = default;
    Material(Color color, Color specular)
        : m_color(color), m_specular(specular) {}

    Color &GetColor() { return this->m_color; }
    Color &GetSpecular() { return this->m_specular; }

private:
    Color m_color;
    Color m_specular;

    std::shared_ptr<IAsset<Texture>> m_diffuseMap;
    std::shared_ptr<IAsset<Texture>> m_normalMap;
};

}

