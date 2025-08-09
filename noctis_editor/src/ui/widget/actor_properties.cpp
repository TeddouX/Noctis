#include "actor_properties.hpp"

#include <engine/ecs/entity.hpp>
#include <engine/scene/scene_manager.hpp>
#include <engine/math/math.hpp>
#include <engine/math/color.hpp>

#include "../../utils/imgui_utils.hpp"
#include "../../utils/property_rendering.hpp"


void ActorPropertiesWidget::Render()
{   
    ImGui::Begin(std::string(ActorPropertiesWidget::name).c_str());

    Scene *currScene = SCENE_MANAGER().GetCurrScene();
    if (!currScene)
    {
        ImGui::End();
        return;
    }

    Entity selectedEntity = currScene->GetSelectedEntity();

    if (currScene && selectedEntity.IsValid())
    {
        auto allComponents = selectedEntity.GetAllComponents();

        std::shared_ptr<Actor> actor = selectedEntity.GetComponent<Actor>();
        // The actor component is handled differently from the others
        // It shouldn't be rendered as a collapsing header
        if (actor)
            HandleActor(actor);
        else
        {
            LOG_ERR("Currently selected entity has no actor associated with it, so it can't be used.");
            ImGui::End();
            return;
        }

        // Transform is processed individually here because it should be inserted at the top of everything
        std::shared_ptr<Transform> transform = selectedEntity.GetComponent<Transform>();
        RenderComponentProperties(transform);

        for (std::shared_ptr<IComponent> component : allComponents)
        {
            // Actor and transform are already handled
            if (std::dynamic_pointer_cast<Actor>(component) || 
                std::dynamic_pointer_cast<Transform>(component))
                continue; 

            RenderComponentProperties(component);
        }  
    }

    ImGui::End();
}


void ActorPropertiesWidget::HandleActor(std::shared_ptr<Actor> actor)
{
    ImGui::SeparatorText("Actor");

    std::string &actorName = actor->GetName();
    ImGui::ResizableInputText("##actor_name_string_input", actorName, true);

    ImGui::SeparatorText("Components");
}
