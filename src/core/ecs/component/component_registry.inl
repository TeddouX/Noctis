#include "component_registry.hpp"


template <typename T>
bool ComponentRegistry::RegisterComponent(const std::string &name)
{
    this->m_componentReg[name] = 
        [](Entity e, ComponentManager &cm, std::shared_ptr<IComponent> comp)
        {
            cm.AddComponent<T>(e, std::static_pointer_cast<T>(comp));
        };
}


template <typename T>
bool ComponentRegistry::RegisterComponentDeserializer(const std::string &name)
{

    this->m_componentDeserializerReg[name] = [](const json &j)
    {
        return std::static_pointer_cast<ISerializable>(
            std::make_shared<T>()
        );
    };
    
    this->RegisterComponent(name);

    return true;
}
