#pragma once
#include "widget.hpp"
#include "../../core/scene/scene_manager.hpp"


class SceneTreeWidget : public IWidget
{
public:
    static constexpr std::string_view name = "Scene Tree";

    void Render() override;

private:
    void IterateActorChildren(const Transform &transform);
};
