#pragma once
#include "system.hpp"
#include "../all_components.hpp"
#include "../component_manager.hpp"
#include "../../../rendering/renderer.hpp"


class RenderSystem : public System 
{
public:
    void Update(const ComponentManager &cm, float dt) const override;
};
