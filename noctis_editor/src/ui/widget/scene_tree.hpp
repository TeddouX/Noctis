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
    static std::string GetName() { return "Scene Tree"; }

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
