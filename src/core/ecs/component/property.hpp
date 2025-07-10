#pragma once
#include <type_traits>
#include <string>
#include <vector>
#include <memory>
#include <any>
#include <unordered_map>
#include <regex>


// This variable is used to define if a class is reflected or not
#define REFLECTED_VARIABLE _reflected

// Mandatory for the use of `PROPERTY` or `PROPERTY_D`
// Any class using this should extend from `IComponent`
#define ENABLE_REFLECTION(CLASSNAME)                                                                                          \
    using _MyClass = CLASSNAME;                                                                                               \
    inline static const bool REFLECTED_VARIABLE = true;                                                                       \
    std::vector<IProperty*> _GetComponentProperties() const override                                                          \
    {                                                                                                                         \
        std::vector<IProperty*> result;                                                                                       \
        for (std::shared_ptr<IProperty> &prop : PropertyRegistry<CLASSNAME>::GetPropertyList())                               \
            result.push_back(prop.get());                                                                                     \
        return result;                                                                                                        \
    }                                                                                                                         \
    const std::string _GetComponentName() const override                                                                      \
    {                                                                                                                         \
        return #CLASSNAME;                                                                                                    \
    } 

    
template <typename _PropTy, typename _ClassTy>
inline bool _RegisterPropertyHelper(const std::string& name, bool hidden, _PropTy _ClassTy::*memberPtr);

template <typename _PropTy, typename _ClassTy>
inline bool _RegisterGetterHelper(const std::string& name, bool hidden, _PropTy (_ClassTy::*getterPtr)());


// A property is a member variable that will be shown in the editor, even if declared as private
#define PROPERTY(TYPE, NAME) \
    TYPE NAME;               \
    inline static const bool _registered_##NAME = _RegisterPropertyHelper(#NAME, false, &_MyClass::NAME);

// A property with a default value
#define PROPERTY_D(TYPE, NAME, DEFAULT_VALUE) \
    TYPE NAME = DEFAULT_VALUE;                \
    inline static const bool _registered_##NAME = _RegisterPropertyHelper(#NAME, false, &_MyClass::NAME);

// A property that is hidden in the editor
#define PROPERTY_HIDDEN(TYPE, NAME, DEFAULT_VALUE) \
    TYPE NAME = DEFAULT_VALUE;                \
    inline static const bool _registered_##NAME = _RegisterPropertyHelper(#NAME, true, &_MyClass::NAME);


// The getter function must return a non const reference to the member variable
#define PROPERTY_GETTER(NAME) inline static const bool _registered_##NAME = _RegisterGetterHelper(#NAME, false, &_MyClass::NAME);

// A property that is hidden in the editor
// The getter function must return a non const reference to the member variable
#define PROPERTY_GETTER_HIDDEN(NAME) inline static const bool _registered_##NAME = _RegisterGetterHelper(#NAME, true, &_MyClass::NAME);


// Example: IsItABanana -> Is It A Banana
extern std::string SplitStringAtCapital(std::string &str);


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
    virtual bool IsHidden() const = 0;
    virtual const std::string &GetName() const = 0;
    virtual std::string GetBeautifiedName() const = 0;
    virtual std::any GetValue(void *instance) const = 0;
};


// Reprensents a member variable in a class C
template <typename T, typename C>
class MemberProperty : public IProperty
{
public:
    using _MemberVar = T C::*;

    MemberProperty(const std::string &name, bool hidden, _MemberVar member)
        : m_name(name), m_member(member), m_hidden(hidden) {};

    bool IsHidden() const override { return this->m_hidden; }

    inline const std::string &GetName() const override { return this->m_name; }
    std::string GetBeautifiedName() const override;

    std::any GetValue(void *C_instance) const override;

private:
    bool m_hidden;
    std::string m_name;
    _MemberVar m_member;
};


template <typename T, typename C>
class GetterProperty : public IProperty
{
public:
    using _GetterFun = T &(C::*)();

    GetterProperty(const std::string &name, bool hidden, _GetterFun getter)
        : m_name(name), m_getter(getter), m_hidden(hidden) {};

    bool IsHidden() const override { return this->m_hidden; }

    inline const std::string &GetName() const override { return this->m_name; }
    std::string GetBeautifiedName() const override;
    
    std::any GetValue(void *C_instance) const override;

private:
    bool m_hidden;
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
