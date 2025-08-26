#include "ecs/component/component.hpp"

namespace Noctis
{

void to_json(json &j, const std::shared_ptr<IComponent> &ptr)
{
    if (ptr)
    {
        ptr->Serialize(j);
        if (!j.contains("type"))
            LOG_WARN(
                "Serialized component has no type defined, this may cause errors. JSON is: {}", 
                j.dump()
            );
    }
    else
        j = nullptr;
}


void from_json(const json &j, std::shared_ptr<IComponent> &ptr)
{
    if (j.is_null())
    {
        ptr = nullptr;
        return;
    }

    if (!j.contains("type"))
    {
        LOG_ERR("Serialized component has no type defined: {}", j.dump());
        return;
    }

    std::string type = j.at("type");
    if (!COMPONENT_REGISTRY().HasComponentDeserializer(type))
    {
        LOG_ERR("Unknown type for deserialization: {}", type);
        ptr = nullptr;
        return;
    }

    ptr = COMPONENT_REGISTRY().GetEntry(type).untypedGetterFun();
    
    // Try deserializing and catch any exceptions
    try 
    {
        ptr->Deserialize(j);
    }
    catch (const std::exception &e)
    {
        LOG_ERR("Error while deserializing component {}: {}", type, e.what());
    }
}

}
