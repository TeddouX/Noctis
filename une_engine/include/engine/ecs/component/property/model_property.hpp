#pragma once
#include "property.hpp"
#include "../../../rendering/model.hpp"


class UNE_API ModelProperty : public IProperty<Model>
{
public:
    ModelProperty(
        std::function<Model &(void)> getter,
        const std::string &name
    ) : m_getter(getter),
        m_name(name) {}

    const std::string &GetName() const override { return this->m_name; }
    Model &GetValue() const override { return this->m_getter(); }

private:
    std::function<Model &(void)> m_getter;
    std::string m_name;
};
