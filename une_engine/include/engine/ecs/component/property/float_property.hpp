#pragma once
#include <float.h>
#include <functional>

#include "property.hpp"


class FloatProperty : public IProperty<float>
{
public:
    FloatProperty(
        std::function<float &(void)> getter, 
        const std::string &name, 
        float minValue = FLT_MIN, 
        float maxValue = FLT_MAX, 
        float stepSize = .1f
    ) : m_getter(getter),
        m_name(name),
        minVal(minValue),
        maxVal(maxValue),
        stepSize(stepSize) {}

    float minVal, maxVal;
    float stepSize;

    const std::string &GetName() const override { return this->m_name; }
    float &GetValue() const override { return this->m_getter(); }

private:
    std::function<float &(void)> m_getter;
    std::string m_name;
    
};
