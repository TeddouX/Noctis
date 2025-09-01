#pragma once
#include <nlohmann/json.hpp>

#include "component_registry.hpp"
#include "../entity.hpp"
#include "../../property/property.hpp"
#include "../../property/property_holder.hpp"
#include "../../logger.hpp"


using json = nlohmann::json;

namespace Noctis
{

class NOCTIS_API IComponent : public IPropertyHolder
{
public:
    virtual std::vector<std::shared_ptr<IPropertyBase>> GetProperties() override { return {}; }
    virtual std::string GetName() const override = 0; 

    virtual void Serialize(json &j) const = 0;
    virtual void Deserialize(const json &j) = 0;
};

/// @brief Serializing components that inherit from IComponent
void to_json(json &j, const std::shared_ptr<IComponent> &ptr);


/// @brief Deserializing components that inherit from IComponent
void from_json(const json &j, std::shared_ptr<IComponent> &ptr);

}


/// @brief Support for serializing shared pointers
template <typename T>
void to_json(json &j, const std::shared_ptr<T> &ptr);


/// @brief Support for deserializing shared pointers
template <typename T>
void from_json(const json &j, std::shared_ptr<T> &ptr);


#include "component.inl"
