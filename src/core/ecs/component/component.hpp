#pragma once
#include <nlohmann/json.hpp>

#include "property.hpp"
#include "../../logger.hpp"



using json = nlohmann::json;



class IComponent
{
public:
    virtual std::vector<IProperty *> _GetComponentProperties() const = 0;
    virtual const std::string _GetComponentName() const = 0;
};



class ISerializable
{
public:
    virtual void Serialize(json &j) const = 0;
    virtual void Deserialize(const json &j) = 0;
};



using ComponentDeserializeFun = std::shared_ptr<ISerializable>(*)(const json&);
inline std::unordered_map<std::string, ComponentDeserializeFun> componentDeserializerReg;



template<typename T>
std::shared_ptr<ISerializable> ComponentDeserializer(const json& j);


template <typename T>
bool RegisterComponentDeserializer(const std::string &componentName);



/// @brief Serializing components that inherit from ISerializable
void to_json(json &j, const std::shared_ptr<ISerializable> &ptr);


/// @brief Deserializing components that inherit from ISerializable
void from_json(const json &j, std::shared_ptr<ISerializable> &ptr);



/// @brief Support for serializing shared pointers
template<typename T>
inline void to_json(json &j, const std::shared_ptr<T> &ptr);


/// @brief Support for deserializing shared pointers
template<typename T>
inline void from_json(const json &j, std::shared_ptr<T> &ptr);



#include "component.inl"
