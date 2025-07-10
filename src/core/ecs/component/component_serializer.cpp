#include "component_serializer.hpp"


json ComponentSerializer::Serialize(std::shared_ptr<IComponent> component)
{
    std::string name = component->_GetComponentName();
    std::vector<IProperty *> properties = component->_GetComponentProperties();

    json serialized{
        {"componentName", name}
    };

    json allProperties = json::array();
    for (IProperty *propery : properties)
    {
        std::any value = propery->GetValue(component.get());
        json serializedValue = SerializeValue(value);

        allProperties.push_back(serializedValue);
    }

    serialized.emplace("properties", allProperties);

    return serialized;
}


std::shared_ptr<IComponent> ComponentSerializer::Deserialize(const json &data)
{
    return nullptr;
}


json ComponentSerializer::SerializeValue(const std::any &value)
{
    if (Is<int>(value.type()))
        return ScalarJSON<int>(value, "int");
    else if (Is<float>(value.type()))
        return ScalarJSON<float>(value, "float");
    else if (Is<Vec3>(value.type()))
    {
        Vec3 &v = Unwrap<Vec3>(value);
        return json{
            {"type", "vec3"}, 
            {"value", {v.x, v.y, v.z}}
        };
    }
    else if (Is<std::shared_ptr<Actor>>(value.type()))
    {
        auto &actor = Unwrap<std::shared_ptr<Actor>>(value);
        return json{
            {"type", "actor"},
            {"value", boost::uuids::to_string(actor->GetUUID())}
        };
    }
    else if (Is<Transform *>(value.type()))
    {
        Transform *&t = Unwrap<Transform *>(value);
        return json{
            {"type", "transform"},
            // Sadly this is the only to identify a transform for now
            // Maybe add a unique identifier for each component but that looks 
            // annoying to implement.
            {"value", t ? boost::uuids::to_string(t->GetActor()->GetUUID()) : ""}
        };
    }
    
    LOG_ERR("Unsupported type for serialization: {}", value.type().name())
    return json{};
}
