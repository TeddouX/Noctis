#pragma once
#include "property.hpp"
#include "../math/color.hpp"

namespace Noctis
{

class NOCTIS_API ColorProperty : public IProperty<Color>
{
public:
    ColorProperty(
        std::function<Color &(void)> getter,
        const std::string& name
    ) : m_getter(getter),
        m_name(name) { }

    const std::string& GetName() const override { return this->m_name; }
    Color& GetValue() const override { return this->m_getter(); }

private:
    std::function<Color &(void)> m_getter;
    std::string m_name;
};

}
