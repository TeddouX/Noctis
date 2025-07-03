#pragma once
#include "system.hpp"
#include "../components/model_component.hpp"
#include "../components/transform.hpp"
#include "../component_manager.hpp"
#include "../entity.hpp"
#include "../../../rendering/renderer.hpp"


class RenderSystem : public ISystem 
{
public:
    void Update(const ComponentManager &cm, float dt) const override;
};
