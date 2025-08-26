#include "ecs/component/component_registry.hpp"
#include "ecs/component/component.hpp"

namespace Noctis
{

ComponentRegistry &ComponentRegistry::GetInstance()
{
    static ComponentRegistry compReg;
    return compReg;
}
    

bool ComponentRegistry::AddComponentFromName(const std::string &name, Entity e, std::shared_ptr<IComponent> comp) const
{
    if (this->m_componentReg.contains(name)) 
        return this->m_componentReg.at(name).addComponentFun(e, comp);
    else 
    {
        LOG_ERR("Component {} is not registered.", name);
        return false;
    }
}


bool ComponentRegistry::HasComponentDeserializer(const std::string &comp) const
{
    return this->m_componentReg.contains(comp);
}


ComponentRegEntry ComponentRegistry::GetEntry(const std::string &comp) const
{
    return this->m_componentReg.at(comp);
}

}
