#pragma once
#include <engine/ecs/entity.hpp>
#include <engine/ecs/component/property.hpp>
#include <engine/ecs/component/actor.hpp>
#include <engine/scene/scene_manager.hpp>
#include <engine/math/math.hpp>
#include <engine/math/color.hpp>

#include "widget.hpp"
#include "../imgui_utils.hpp"



class ActorPropertiesWidget : public IWidget
{
public:
    static constexpr std::string_view name = "Actor Properties";

    void Render() override;

private:
    static void IterateComponentProperties(std::shared_ptr<IComponent> component);
    static void HandleActor(IComponent *component);
    static void ProcessProperty(IProperty *property, IComponent *component);
    static std::string GenImGuiID(std::string prefix, IProperty *property, IComponent *component);
};
