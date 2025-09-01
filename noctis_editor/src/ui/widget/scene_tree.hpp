#pragma once
#include "widget.hpp"

namespace Noctis
{
    class Entity;
    class Transform;
}

namespace NoctisEditor
{

class SceneTreeWidget : public IWidget
{
public:
    static constexpr std::string_view name = "Scene Tree";

    void Render() override;

private:
    void IterateTransformChildren(
        Noctis::Transform *transform, 
        const Noctis::Entity &entity
    );
    void HandleActorCreationMenu(Noctis::Transform *parent);
    void HandleDragDropTarget(Noctis::Transform *parent);
};

}
