#pragma once
#include <nlohmann/json.hpp>

#include "property.hpp"
#include "component_registry.hpp"
#include "../entity.hpp"
#include "../../logger.hpp"


using json = nlohmann::json;


class IComponent
{
public:
    virtual std::vector<IProperty *> _GetComponentProperties() const = 0;
    virtual const std::string _GetComponentName() const = 0;
};


/// @brief Support for serializing shared pointers
template <typename T>
inline void to_json(json &j, const std::shared_ptr<T> &ptr);


/// @brief Support for deserializing shared pointers
template <typename T>
inline void from_json(const json &j, std::shared_ptr<T> &ptr);


#include "component.inl"
