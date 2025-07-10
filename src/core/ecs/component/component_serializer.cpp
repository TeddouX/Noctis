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
            {"type", "actor_shared_ptr"},
            {"value", boost::uuids::to_string(actor->GetUUID())}
        };
    }
    else if (Is<Transform *>(value.type()))
    {
        Transform *&t = Unwrap<Transform *>(value);
        return json{
            {"type", "transform_ptr"},
            // Sadly, this is the only to identify a transform for now
            // Maybe add a unique identifier for each component, but that looks 
            // annoying to implement and use.
            {"value", t ? boost::uuids::to_string(t->GetActor()->GetUUID()) : ""}
        };
    }
    
    LOG_ERR("Unsupported type for serialization: {}", value.type().name())
    return json{};
}


void ComponentSerializer::DeserializeProperty(const json &propJson, IProperty *property, std::shared_ptr<IComponent> component)
{
    std::string propType = propJson["type"];
    std::any value = property->GetValue(component.get());

    if (propType == "int")
        Unwrap<int>(value) = propJson["value"];
    else if (propType == "float")
        Unwrap<float>(value) = propJson["value"];
    else if (propType == "vec3")
        Unwrap<Vec3>(value) = Vec3(
            propJson["value"][0], 
            propJson["value"][1], 
            propJson["value"][2]
        ); 
    else if (propType == "actor_shared_ptr")
    {
        auto actor = std::make_shared<Actor>(
            boost::uuids::string_generator()(propJson["value"].get<std::string>())
        );
        Unwrap<std::shared_ptr<Actor>>(value) = actor;
    }
    else if (propType == "transform_ptr")
    {
        std::string uuid = propJson["value"].get<std::string>();
        std::shared_ptr<Actor> actor;

        if (!uuid.empty())
            actor = std::make_shared<Actor>(
                boost::uuids::string_generator()(uuid)
            );

        Unwrap<Transform *>(value) = nullptr;
    }
}
