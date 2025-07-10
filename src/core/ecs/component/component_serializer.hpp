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
    static std::shared_ptr<IComponent> Deserialize(const json &data);

private:
    static json SerializeValue(const std::any &value);

    template <typename T>
    static inline json ScalarJSON(const std::any &value, const std::string &typeName)
    {
        return json{
            {"type", typeName}, 
            {"value", std::any_cast<std::reference_wrapper<T>>(value).get()}
        };
    }

    template <typename T>
    static inline T &Unwrap(const std::any& value) 
    { 
        return std::any_cast<std::reference_wrapper<T>>(value).get(); 
    }

    template <typename T>
    static bool Is(const type_info &ti)
    {
        return ti == typeid(std::reference_wrapper<T>);
    }
};
