#include "component.hpp"


template<typename T>
std::shared_ptr<ISerializable> ComponentDeserializer(const json& j) 
{
    return std::static_pointer_cast<ISerializable>(
        std::make_shared<T>()
    );
}


template <typename T>
bool RegisterComponentDeserializer(const std::string &componentName)
{
    ::componentDeserializerReg[componentName] = &ComponentDeserializer<T>;
    return true;
}


/// @brief Support for serializing shared pointers
template<typename T>
void to_json(json &j, const std::shared_ptr<T> &ptr) 
{
    if (ptr)
        j = *ptr;
    else
        j = nullptr;
}

/// @brief Support for deserializing shared pointers
template<typename T>
void from_json(const json &j, std::shared_ptr<T> &ptr) 
{
    if (!j.is_null())
    {
        ptr = std::make_shared<T>();
        from_json(j, *ptr);
    }
    else
        ptr = nullptr;       
}