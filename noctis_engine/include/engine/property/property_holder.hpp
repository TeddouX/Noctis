#pragma once
#include <vector>
#include <memory>

#include "property.hpp"

namespace Noctis
{

class IPropertyHolder
{
    virtual std::vector<std::shared_ptr<IPropertyBase>> GetProperties() = 0;
};

}