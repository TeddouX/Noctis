#pragma once
#include <engine/ecs/entity.hpp>
#include <engine/ecs/component/actor_component.hpp>
#include <engine/scene/scene_manager.hpp>
#include <engine/math/math.hpp>
#include <engine/math/color.hpp>

#include "widget.hpp"
#include "../../utils/imgui_utils.hpp"
#include "../../utils/property_rendering.hpp"



class ActorPropertiesWidget : public IWidget
{
public:
    static constexpr std::string_view name = "Actor Properties";

    void Render() override;

private:
    static void HandleActor(Actor *component);
};
