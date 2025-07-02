#pragma once
#include "system.hpp"
#include "../all_components.hpp"
#include "../component_manager.hpp"
#include "../entity.hpp"
#include "../../../rendering/renderer.hpp"


class RenderSystem : public ISystem 
{
public:
    void Update(const ComponentManager &cm, float dt) const override;
};
