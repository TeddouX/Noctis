#pragma once
#include <nlohmann/json.hpp>

#include "component_registry.hpp"
#include "property/property.hpp"
#include "../entity.hpp"
#include "../../logger.hpp"


using json = nlohmann::json;


class NOCTIS_API IComponent
{
public:
    virtual std::vector<std::shared_ptr<IPropertyBase>> GetProperties() { return {}; } 
    virtual std::string GetName() const = 0; 

    virtual void Serialize(json &j) const = 0;
    virtual void Deserialize(const json &j) = 0;
};


/// @brief Support for serializing shared pointers
template <typename T>
inline void to_json(json &j, const std::shared_ptr<T> &ptr);


/// @brief Support for deserializing shared pointers
template <typename T>
inline void from_json(const json &j, std::shared_ptr<T> &ptr);


#include "component.inl"
