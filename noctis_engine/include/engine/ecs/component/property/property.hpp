#pragma once
#include <string>

#include "../../../filesystem.hpp"


#define GETTER_FOR(EXPR) [this]() -> decltype(EXPR) { return EXPR; }
#define GETTER_FOR_REF(EXPR) [this]() -> decltype(EXPR)& { return EXPR; }

namespace Noctis
{

/// @brief Any pointer of type IPropertyBase should be castable to IProperty
class NOCTIS_API IPropertyBase
{
public:
    virtual ~IPropertyBase() = default;
    virtual const std::string& GetName() const = 0;
};


template <typename T>
class NOCTIS_API IProperty : public IPropertyBase
{
public:
    virtual T &GetValue() const = 0;
};

}
