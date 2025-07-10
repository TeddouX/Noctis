#pragma once
#include "widget.hpp"
#include "../imgui_utils.hpp"
#include "../../core/ecs/entity.hpp"
#include "../../core/ecs/component/property.hpp"
#include "../../core/ecs/component/actor.hpp"
#include "../../core/scene/scene_manager.hpp"
#include "../../core/math/math.hpp"
#include "../../core/math/color.hpp"


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
