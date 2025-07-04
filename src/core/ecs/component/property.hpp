#pragma once
#include <type_traits>
#include <string>
#include <vector>
#include <memory>
#include <any>
#include <unordered_map>


// Mandatory for the use of `PROPERTY` or `PROPERTY_D`
#define ENABLE_REFLECTION(CLASSNAME)                                                                                          \
    using _MyClass = CLASSNAME;                                                                                               \
    template <typename T>                                                                                                     \
    static bool RegisterPropertyHelper(const std::string& name, T _MyClass::*memberPtr)                                       \
    {                                                                                                                         \
        PropertyRegistry<CLASSNAME>::RegisterProperty(name, std::make_unique<MemberProperty<T, CLASSNAME>>(name, memberPtr)); \
        return true;                                                                                                          \
    }                                                                                                                         \
    template <typename T>                                                                                                     \
    static bool RegisterGetterHelper(const std::string& name, T (_MyClass::*getterPtr)())                                     \
    {                                                                                                                         \
        PropertyRegistry<CLASSNAME>::RegisterProperty(name, std::make_unique<GetterProperty<T, CLASSNAME>>(name, getterPtr)); \
        return true;                                                                                                          \
    }                                                                                                                         \
    std::vector<IProperty*> GetProperties()                                                                                   \
    {                                                                                                                         \
        std::vector<IProperty*> result;                                                                                       \
        for (std::shared_ptr<IProperty> &prop : PropertyRegistry<CLASSNAME>::GetPropertyList())                               \
            result.push_back(prop.get());                                                                                     \
        return result;                                                                                                        \
    }

// A property is a member variable that will be shown in the editor, even if declared as private
#define PROPERTY(TYPE, NAME) \
    TYPE NAME;               \
    inline static const bool _registered_##NAME = _MyClass::RegisterPropertyHelper(#NAME, &_MyClass::NAME);

// A property with a default value
#define PROPERTY_D(TYPE, NAME, DEFAULT_VALUE) \
    TYPE NAME = DEFAULT_VALUE;                \
    inline static const bool _registered_##NAME = _MyClass::RegisterPropertyHelper(#NAME, &_MyClass::NAME);


// The getter function has to return a non const reference to the member variable
// Support for getter-setter functions will be added later
#define PROPERTY_GETTER(NAME) inline static const bool _registered_##NAME = _MyClass::RegisterGetterHelper(#NAME, &_MyClass::NAME);


// Interface that holds functionality for a property
class IProperty
{
public:
    virtual const std::string &GetName() const = 0;
    virtual std::any GetValue(void *instance) const = 0;
};


// Reprensents a member variable in a class C
template <typename T, typename C>
class MemberProperty : public IProperty
{
public:
    MemberProperty(const std::string &name, T C::*member)
        : m_name(name), m_member(member) {};

    inline const std::string &GetName() const override { return this->m_name; }

    std::any GetValue(void *C_instance) const override;

private:
    std::string m_name;
    T C::*m_member;
};


template <typename T, typename C>
class GetterProperty : public IProperty
{
public:
    GetterProperty(const std::string &name, T &(C::*getter)())
        : m_name(name), m_getter(getter) {};

    inline const std::string &GetName() const override { return this->m_name; }
    
    std::any GetValue(void *C_instance) const override;

private:
    std::string m_name;
    T &(C::*m_getter)(); 
};


// Used to store properties outside the class
template <typename C>
class PropertyRegistry
{
public:
    static void RegisterProperty(const std::string &name, std::shared_ptr<IProperty> prop);

    static std::vector<std::shared_ptr<IProperty>> &GetPropertyList();
};


#include "property.inl"
