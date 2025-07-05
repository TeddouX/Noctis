#pragma once
#include <type_traits>
#include <string>
#include <vector>
#include <memory>
#include <any>
#include <unordered_map>


#define REFLECTED_VARIABLE _reflected

// Mandatory for the use of `PROPERTY` or `PROPERTY_D`
// Any class using this should extend from `IComponent`
#define ENABLE_REFLECTION(CLASSNAME)                                                                                          \
    using _MyClass = CLASSNAME;                                                                                               \
    inline static const bool REFLECTED_VARIABLE = true;                                                                       \
    template <typename T>                                                                                                     \
    static bool _RegisterPropertyHelper(const std::string& name, T _MyClass::*memberPtr)                                       \
    {                                                                                                                         \
        PropertyRegistry<CLASSNAME>::RegisterProperty(name, std::make_unique<MemberProperty<T, CLASSNAME>>(name, memberPtr)); \
        return true;                                                                                                          \
    }                                                                                                                         \
    template <typename T>                                                                                                     \
    static bool _RegisterGetterHelper(const std::string& name, T (_MyClass::*getterPtr)())                                     \
    {                                                                                                                         \
        PropertyRegistry<CLASSNAME>::RegisterProperty(name, std::make_unique<GetterProperty<T, CLASSNAME>>(name, getterPtr)); \
        return true;                                                                                                          \
    }                                                                                                                         \
    std::vector<IProperty*> _GetComponentProperties() const override                                                                    \
    {                                                                                                                         \
        std::vector<IProperty*> result;                                                                                       \
        for (std::shared_ptr<IProperty> &prop : PropertyRegistry<CLASSNAME>::GetPropertyList())                               \
            result.push_back(prop.get());                                                                                     \
        return result;                                                                                                        \
    }                                                                                                                         \
    const std::string _GetComponentName() const override                                                                     \
    {                                                                                                                         \
        return #CLASSNAME;                                                                                                    \
    } 


// A property is a member variable that will be shown in the editor, even if declared as private
#define PROPERTY(TYPE, NAME) \
    TYPE NAME;               \
    inline static const bool _registered_##NAME = _MyClass::_RegisterPropertyHelper(#NAME, &_MyClass::NAME);

// A property with a default value
#define PROPERTY_D(TYPE, NAME, DEFAULT_VALUE) \
    TYPE NAME = DEFAULT_VALUE;                \
    inline static const bool _registered_##NAME = _MyClass::_RegisterPropertyHelper(#NAME, &_MyClass::NAME);


// The getter function has to return a non const reference to the member variable
// Support for getter-setter functions will be added later
#define PROPERTY_GETTER(NAME) inline static const bool _registered_##NAME = _MyClass::_RegisterGetterHelper(#NAME, &_MyClass::NAME);


// Fallback if the _Class::_reflected doesn't exist
template <typename _Class, typename _Type = bool>
struct IsReflected : std::false_type {};

// Undefined behaviour if _Class::_reflected doesn't exist so it falls back to the first one (SFINAE)
template <typename _Class>
struct IsReflected<_Class, decltype((void) _Class::REFLECTED_VARIABLE, true)> : std::true_type {};


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
    using _MemberVar = T C::*;

    MemberProperty(const std::string &name, _MemberVar member)
        : m_name(name), m_member(member) {};

    inline const std::string &GetName() const override { return this->m_name; }

    std::any GetValue(void *C_instance) const override;

private:
    std::string m_name;
    _MemberVar m_member;
};


template <typename T, typename C>
class GetterProperty : public IProperty
{
public:
    using _GetterFun = T &(C::*)();

    GetterProperty(const std::string &name, _GetterFun getter)
        : m_name(name), m_getter(getter) {};

    inline const std::string &GetName() const override { return this->m_name; }
    
    std::any GetValue(void *C_instance) const override;

private:
    std::string m_name;
    _GetterFun m_getter; 
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
