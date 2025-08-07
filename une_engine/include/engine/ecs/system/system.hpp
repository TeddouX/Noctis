#pragma once
#include "../component_manager.hpp"


class ISystem
{
public:
    virtual ~ISystem() = default;

    // Start is called once
    virtual void Start(ComponentManager &cm) {};
    // Update is called every frame
    virtual void Update(ComponentManager &cm, float dt) = 0;
};
