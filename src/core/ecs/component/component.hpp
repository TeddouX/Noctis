#pragma once
#include "property.hpp"


class IComponent
{
public:
    virtual std::vector<IProperty*> _GetComponentProperties() const = 0;
    virtual const std::string _GetComponentName() const = 0;
};
