#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>

#include "../entity.hpp"
#include "../component_manager.hpp"


#define COMPONENT_REGISTRY() ComponentRegistry::GetInstance()

#define REGISTER_COMPONENT(CLASSNAME, NAME) inline static const bool __serializable##CLASSNAME = \
    ComponentRegistry::GetInstance().RegisterComponent<CLASSNAME>(NAME); \
    std::string GetName() const override { return NAME; }

#define START_SERIALIZATION(JSON) JSON = json { {"type", this->GetName()},
#define END_SERIALIZATION() };

/// @brief Helper macro for serializing a member variable
#define PROP_TO_JSON(PROPERTY) {#PROPERTY, PROPERTY}


/// @brief Helper macro for getting a member
/// variable from a json object
#define PROP_FROM_JSON(JSON, PROPERTY) JSON.at(#PROPERTY).get_to(PROPERTY);


using json = nlohmann::json;


class IComponent;


struct NOCTIS_API ComponentRegEntry
{
    using AddComponentFun = std::function<bool (Entity, std::shared_ptr<IComponent>)>;
    using RemoveComponentFun = std::function<void (Entity)>;
    using UntypedGetterFun = std::function<std::shared_ptr<IComponent> (void)>;

    AddComponentFun addComponentFun;
    RemoveComponentFun removeComponentFun;
    UntypedGetterFun untypedGetterFun;
};


/// @brief This class helps for component deserialization
class NOCTIS_API ComponentRegistry
{
public:
    static ComponentRegistry &GetInstance();

    /// @brief Adds a component to the registry so it can be used when deserializing 
    template <typename T>
    bool RegisterComponent(const std::string &name);

    /// @brief Adds component from name to an entity
    bool AddComponentFromName(const std::string &name, Entity e, std::shared_ptr<IComponent> comp) const;

    /// @return `true` if the registry has a deserilier for the 
    /// component of name `comp`
    bool HasComponentDeserializer(const std::string &comp) const;

    /// @returns The deserilizer function associated 
    /// with the component of name `comp`
    ComponentRegEntry GetEntry(const std::string &comp) const;

    const std::unordered_map<std::string, ComponentRegEntry> &GetAllComponents() { return this->m_componentReg; }

private:
    std::unordered_map<std::string, ComponentRegEntry> m_componentReg;
};


/// @brief Serializing components that inherit from IComponent
void to_json(json &j, const std::shared_ptr<IComponent> &ptr);


/// @brief Deserializing components that inherit from IComponent
void from_json(const json &j, std::shared_ptr<IComponent> &ptr);


#include "component_registry.inl"
