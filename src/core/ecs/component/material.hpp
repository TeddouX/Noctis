#pragma once
#include <string>
#include <memory>

#include "component.hpp"
#include "../../../rendering/shader.hpp"


class Material : public IComponent
{
public:
    ENABLE_REFLECTION(Material)

    Material(const std::string &name, std::shared_ptr<Shader> shader)
        : m_name(name), m_shader(shader) {};

    inline std::string &GetName() { return this->m_name; }
    PROPERTY_GETTER(GetName)
    
    inline std::shared_ptr<Shader> &GetShader() { return this->m_shader; }
    PROPERTY_GETTER(GetShader)

private:
    std::string             m_name;
    std::shared_ptr<Shader> m_shader;
};
