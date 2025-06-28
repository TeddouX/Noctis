#pragma once
#include "../component_manager.hpp"


class System
{
public:
    virtual void Update(const ComponentManager &cm, float dt) const {};
};
