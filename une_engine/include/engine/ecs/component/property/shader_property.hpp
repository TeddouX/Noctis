#pragma once
#include "property.hpp"
#include "../../../rendering/shader.hpp"


class UNE_API ShaderProperty : public IProperty<Shader>
{
public:
    ShaderProperty(
        std::function<Shader &(void)> getter,
        const std::string &name
    ) : m_getter(getter),
        m_name(name) {}

    const std::string &GetName() const override { return this->m_name; }
    Shader &GetValue() const override { return this->m_getter(); }

private:
    std::function<Shader &(void)> m_getter;
    std::string m_name;
};
