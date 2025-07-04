#pragma once
#include <type_traits>
#include <string>
#include <vector>
#include <memory>
#include <any>
#include <unordered_map>



#define ENABLE_REFLECTION(CLASSNAME)                                                                                             \
    using _MyClass = CLASSNAME;                                                                                                  \
    static bool RegisterPropertyHelper(const std::string& name, auto memberPtr)                                                  \
    {                                                                                                                            \
        using _ValueType = std::remove_reference_t<decltype(std::declval<CLASSNAME>().*memberPtr)>;                              \
        PropertyRegistry<CLASSNAME>::RegisterProperty(name, std::make_unique<Property<_ValueType, CLASSNAME>>(name, memberPtr)); \
        return true;                                                                                                             \
    }                                                                                                                            \
    std::vector<IProperty*> GetProperties()                                                                                      \
    {                                                                                                                            \
        std::vector<IProperty*> result;                                                                                          \
        for (auto& prop : PropertyRegistry<CLASSNAME>::GetPropertyList())                                                        \
            result.push_back(prop.get());                                                                                        \
        return result;                                                                                                           \
    }

    
#define PROPERTY(TYPE, NAME) \
    TYPE NAME;               \
    inline static const bool _registered_##NAME = _MyClass::RegisterPropertyHelper(#NAME, &_MyClass::NAME);


#define PROPERTY_D(TYPE, NAME, DEFAULT_VALUE) \
    TYPE NAME = DEFAULT_VALUE;                \
    inline static const bool _registered_##NAME = _MyClass::RegisterPropertyHelper(#NAME, &_MyClass::NAME);


class IProperty
{
public:
    virtual const std::string &GetName() const = 0;
    virtual std::any GetProperty(void *instance) const = 0;
};


template <typename T, typename C>
class Property : public IProperty
{
public:
    Property(const std::string &name, T C::*member);

    inline const std::string &GetName() const override { return this->m_name; }

    std::any GetProperty(void *C_instance) const override;

private:
    std::string m_name;
    T C::* m_member;
};


template <typename C>
class PropertyRegistry
{
public:
    static void RegisterProperty(const std::string &name, std::shared_ptr<IProperty> prop);

    static std::vector<std::shared_ptr<IProperty>> &GetPropertyList();
};


#include "property.inl"
