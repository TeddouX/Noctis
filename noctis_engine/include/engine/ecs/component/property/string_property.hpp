#pragma once
#include <functional>

#include "property.hpp"


class NOCTIS_API StringProperty: public IProperty<std::string>
{
public:
    StringProperty(
        std::function<std::string &(void)> getter,
        const std::string& name
    ) : m_getter(getter),
        m_name(name) { }

    const std::string& GetName() const override { return this->m_name; }
    std::string& GetValue() const override { return this->m_getter(); }

private:
    std::function<std::string &(void)> m_getter;
    std::string m_name;
};