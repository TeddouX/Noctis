#pragma once
#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include "actor.hpp"
#include "transform.hpp"
#include "component.hpp"
#include "../../math/math.hpp"
#include "../../logger.hpp"


using json = nlohmann::json;


class ComponentSerializer
{
public:
    static json Serialize(std::shared_ptr<IComponent> component);

    template <typename T>
    static std::shared_ptr<T> Deserialize(const json &data);

private:
    static json SerializeValue(const std::any &value);
    static void DeserializeProperty(const json &propJson, IProperty *property, std::shared_ptr<IComponent> component);

    template <typename T>
    static inline json ScalarJSON(const std::any &value, const std::string &typeName)
    {
        return json{
            {"type", typeName}, 
            {"value", Unwrap<T>(value)}
        };
    }
};

#include "component_serializer.inl"
