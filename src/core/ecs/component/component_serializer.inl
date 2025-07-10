#include "component_serializer.hpp"


template <typename T>
std::shared_ptr<T> ComponentSerializer::Deserialize(const json &data)
{
    static_assert(std::is_base_of<IComponent, T>(), "T must inherit from IComponent.");
    static_assert(std::is_default_constructible<T>(), "T must have a default constructor.");

    std::shared_ptr<T> component = std::make_shared<T>();
    std::vector<IProperty *> componentProperties = component->_GetComponentProperties();

    const json &properties = data.at("properties");
    for (int i = 0; i < properties.size(); i++)
    {
        const json &property = properties[i];
        IProperty *componentProperty = componentProperties[i];

        DeserializeProperty(property, componentProperty, component);
    }

    return component;
}
