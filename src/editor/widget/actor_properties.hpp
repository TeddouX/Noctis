#pragma once
#include "widget.hpp"
#include "../../core/imgui_utils.hpp"
#include "../../core/ecs/entity.hpp"
#include "../../core/ecs/component/property.hpp"
#include "../../core/scene/scene_manager.hpp"


class ActorPropertiesWidget : public IWidget
{
public:
    static constexpr std::string_view name = "Actor Properties";

    void Render() override;

private:
    static void ActorComponent(IComponent *component);
    static void ProcessProperty(IProperty *property, IComponent *component);
    static std::string GenImGuiID(std::string prefix, IProperty *property, IComponent *component);
};
