#pragma once
#include <engine/scene/scene_manager.hpp>

#include "widget.hpp"
#include "../../utils/actor_creation_helper.hpp"


class SceneTreeWidget : public IWidget
{
public:
    static constexpr std::string_view name = "Scene Tree";

    void Render() override;

private:
    static void IterateTransformChildren(Transform *transform, const Entity &entity);
    static void HandleActorCreationMenu(Transform *parent);
    static void HandleDragDropTarget(Transform *parent);
};
