#pragma once
#include <vector>
#include <memory>

#include "property.hpp"

namespace Noctis
{

class IPropertyHolder
{
public:
    virtual std::vector<std::shared_ptr<IPropertyBase>> GetProperties() = 0;
    virtual std::string GetName() const = 0;
};

}