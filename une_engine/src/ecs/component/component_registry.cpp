#include "ecs/component/component_registry.hpp"


ComponentRegistry &ComponentRegistry::GetInstance()
{
    static ComponentRegistry compReg;
    return compReg;
}
    

void ComponentRegistry::AddComponentFromName(const std::string &name, Entity e, ComponentManager &cm, std::shared_ptr<IComponent> comp) const
{
    auto it = this->m_componentReg.find(name);
    if (it != this->m_componentReg.end()) 
        it->second(e, cm, comp);
    else 
        LOG_ERR("Component {} is not registered.", name)
}


bool ComponentRegistry::HasComponentDeserializer(const std::string &comp) const
{
    return this->m_componentDeserializerReg.find(comp) 
            != this->m_componentDeserializerReg.end();
}


ComponentRegistry::ComponentDeserializerFun ComponentRegistry::GetDeserializer(const std::string &comp) const
{
    return this->m_componentDeserializerReg.at(comp);
}


void to_json(json &j, const std::shared_ptr<ISerializable> &ptr)
{
    if (ptr)
    {
        ptr->Serialize(j);
        if (!j.contains("type"))
            LOG_WARN(
                "Serialized component has no type defined, this may cause errors. JSON is: {}", 
                j.dump()
            )
    }
    else
        j = nullptr;
}


void from_json(const json &j, std::shared_ptr<ISerializable> &ptr)
{
    if (j.is_null())
    {
        ptr = nullptr;
        return;
    }

    if (!j.contains("type"))
    {
        LOG_ERR("Serialized component has no type defined: {}", j.dump())
        return;
    }

    std::string type = j.at("type");
    if (!ComponentRegistry::GetInstance().HasComponentDeserializer(type))
    {
        LOG_ERR("Unknown type for deserialization: {}", type)
        ptr = nullptr;
        return;
    }

    ptr = ComponentRegistry::GetInstance().GetDeserializer(type)(j);
    
    // Try deserializing and catch any exceptions
    try 
    {
        ptr->Deserialize(j);
    }
    catch (const std::exception &e)
    {
        LOG_ERR("Error while deserializing component: {}", e.what())
    }
}
