#pragma once
#include <string>

#include "../../../filesystem.hpp"


#define GETTER_FOR(EXPR) [this]() -> decltype(EXPR)& { return EXPR; }


/// @brief Any pointer of type IPropertyBase should be castable to IProperty
class UNE_API IPropertyBase
{
public:
    virtual ~IPropertyBase() = default;
    virtual const std::string& GetName() const = 0;
};


template <typename T>
class UNE_API IProperty : public IPropertyBase
{
public:
    virtual T &GetValue() const = 0;
};
