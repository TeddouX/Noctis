#pragma once
#include <engine/ecs/component/actor_component.hpp>

#include "widget.hpp"

namespace NoctisEditor
{

class ActorPropertiesWidget : public IWidget
{
public:
    static constexpr std::string_view name = "Actor Properties";

    void Render() override;

private:
    static void HandleActor(std::shared_ptr<Noctis::Actor> component);
    
    void ShowAddComponentPopup(Noctis::Entity &entity);
    void ShowComponentRightClickPopup(
        std::shared_ptr<Noctis::IComponent> comp, 
        Noctis::Entity &entity, 
        const std::string &popupID
    );
};

}
