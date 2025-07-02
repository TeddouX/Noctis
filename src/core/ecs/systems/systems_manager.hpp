#pragma once
#include <memory>
#include <vector>
#include <typeinfo>

#include "system.hpp"
#include "../component_manager.hpp"
#include "../../logger.hpp"


class SystemsManager
{
    std::vector<std::shared_ptr<ISystem>> m_systems;

public:
    template<typename T, typename... Args>
    T& RegisterSystem(Args &&...args);

    void UpdateAll(ComponentManager cm, float dt);

    template <typename T>
    void UpdateSystem(ComponentManager cm, float dt);
};

#include "systems_manager.inl"
