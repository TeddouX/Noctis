#pragma once
#include "../component_manager.hpp"


class ISystem
{
public:
    virtual ~ISystem() = default;
    virtual void Update(const ComponentManager &cm, float dt) = 0;
};
