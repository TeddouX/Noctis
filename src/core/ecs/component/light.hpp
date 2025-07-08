#include "component.hpp"
#include "../../math/color.hpp"


class DirectionalLight : public IComponent
{
public:
    ENABLE_REFLECTION(DirectionalLight)

    DirectionalLight(Vec3 direction, Color ambient, Color diffuse, Color specular)
        : m_dir(direction), m_ambient(ambient), m_diffuse(diffuse), m_specular(specular) {};

    Vec3 &GetDirection() { return this->m_dir; }
    PROPERTY_GETTER(GetDirection)
    Color &GetAmbientColor() { return this->m_ambient; }
    PROPERTY_GETTER(GetAmbientColor)
    Color &GetDiffuseColor() { return this->m_diffuse; }
    PROPERTY_GETTER(GetDiffuseColor)
    Color &GetSpecularColor() { return this->m_specular; }
    PROPERTY_GETTER(GetSpecularColor)

private:
    Vec3 m_dir;
    Color m_ambient;
    Color m_diffuse;
    Color m_specular;
};
