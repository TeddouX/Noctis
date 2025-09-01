#pragma once
#include "property.hpp"
#include "../math/math.hpp"

namespace Noctis
{

class NOCTIS_API Vec3Property : public IProperty<Vec3>
{
public:
    Vec3Property(
        std::function<Vec3 &(void)> getter,
        const std::string& name,
        bool canComponentsLink = false,
        bool canBeNegative = true
    ) : m_getter(getter),
        m_name(name),
        canComponentsLink(canComponentsLink),
        canBeNegative(canBeNegative) {}

    bool canComponentsLink;
    bool canBeNegative;

    const std::string& GetName() const override { return this->m_name; }
    Vec3& GetValue() const override { return this->m_getter(); }

private:
    std::function<Vec3 &(void)> m_getter;
    std::string m_name;
    bool m_canComponentsLink;
    bool m_canBeNegative;
};

}
