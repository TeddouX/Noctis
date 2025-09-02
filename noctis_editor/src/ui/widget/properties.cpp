#include "properties.hpp"

#include <noctis/ecs/component/actor_component.hpp>
#include <noctis/ecs/component/transform_component.hpp>
#include <noctis/ecs/component/component_registry.hpp>
#include <noctis/ecs/entity.hpp>
#include <noctis/scene/scene_manager.hpp>
#include <noctis/property/property.hpp>
#include <noctis/asset/asset.hpp>
#include <noctis/math/math.hpp>
#include <noctis/math/color.hpp>

#include "../../utils/imgui_utils.hpp"
#include "../../utils/property_rendering.hpp"

namespace NoctisEditor
{

void PropertiesWidget::Render()
{   
    ImGui::Begin(GetName().c_str());

    if (!m_selectedAsset)
    {
        Noctis::Scene *currScene = SCENE_MANAGER().GetCurrScene();
        Noctis::Entity &selectedEntity = currScene->GetSelectedEntity();

        if (currScene && selectedEntity.IsValid())
        {
            auto allComponents = selectedEntity.GetAllComponents();
            auto actor = selectedEntity.GetComponent<Noctis::Actor>();

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
            auto transform = selectedEntity.GetComponent<Noctis::Transform>();
            bool open = ImGui::CollapsingHeader(transform->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen);
            if (open)
                RenderProperties(transform);

            for (std::shared_ptr<Noctis::IComponent> component : allComponents)
            {
                // Actor and transform are already handled
                if (std::dynamic_pointer_cast<Noctis::Actor>(component) || 
                    std::dynamic_pointer_cast<Noctis::Transform>(component))
                    continue; 

                open = ImGui::CollapsingHeader(component->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen);
                
                std::string popupID = "COMPONENT_RIGHT_CLICK_POPUP_" + component->GetName();  
                if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
                    ImGui::OpenPopup(popupID.c_str());
                
                if (open)
                    RenderProperties(component);

                this->ShowComponentRightClickPopup(component, selectedEntity, popupID);

            }

            float buttonWidth = 180;
            float offsetX = (ImGui::GetContentRegionAvail().x - buttonWidth) * .5f;

            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offsetX);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
            
            if (ImGui::Button("Add Component", ImVec2(buttonWidth, 0.f)))
                ImGui::OpenPopup("ADD_COMPONENT_POPUP");

            this->ShowAddComponentPopup(selectedEntity);
        }
    }
    // If an asset is selected 
    else
        RenderProperties(m_selectedAsset);
    

    ImGui::End();
}


void PropertiesWidget::HandleActor(std::shared_ptr<Noctis::Actor> actor)
{
    ImGui::SeparatorText("Actor");

    std::string &actorName = actor->GetName();
    NoctisEditor::ResizableInputText("##actor_name_string_input", actorName, true);

    ImGui::SeparatorText("Components");
}


void PropertiesWidget::ShowAddComponentPopup(Noctis::Entity &entity)
{
    if (ImGui::BeginPopup("ADD_COMPONENT_POPUP"))
    {
        ImGui::SeparatorText("Components");
        
        auto allComponents = Noctis::ComponentRegistry::GetInstance().GetAllComponents();
        for (auto &[name, compRegEntry] : allComponents)
        {
            // You shouldn't be able to add the 
            // actor component to an Actor
            if (name == "Actor")
                continue;

            if (ImGui::Selectable(name.c_str()))
            {
                if (compRegEntry.addComponentFun(entity, compRegEntry.untypedGetterFun()))
                    ImGui::CloseCurrentPopup();
            }
        }

        ImGui::EndPopup();
    }
}


void PropertiesWidget::ShowComponentRightClickPopup(
    std::shared_ptr<Noctis::IComponent> comp, 
    Noctis::Entity &entity, 
    const std::string &popupID)
{
    if (ImGui::BeginPopup(popupID.c_str()))
    {
        if (ImGui::Selectable("Delete"))
            Noctis::ComponentRegistry::GetInstance().GetEntry(comp->GetName()).removeComponentFun(entity);

        ImGui::EndPopup();
    }
}

}
