#pragma once
#include <limits.h>
#include <functional>

#include "property.hpp"


class IntProperty : public IProperty<int>
{
public:
    IntProperty(
        std::function<int &(void)> getter, 
        const std::string &name, 
        int minValue = INT32_MIN, 
        int maxValue = INT32_MAX, 
        int stepSize = 1
    ) : m_getter(getter),
        m_name(name),
        minVal(minValue),
        maxVal(maxValue),
        stepSize(stepSize) {}

    int minVal, maxVal;
    int stepSize;

    const std::string &GetName() const override { return this->m_name; }
    int &GetValue() const override { return this->m_getter(); }

private:
    std::function<int &(void)> m_getter;
    std::string m_name;
};
