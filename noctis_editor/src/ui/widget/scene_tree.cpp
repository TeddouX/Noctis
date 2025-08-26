#include "scene_tree.hpp"

#include <engine/scene/scene_manager.hpp>

namespace NoctisEditor
{

void SceneTreeWidget::Render()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin(std::string(SceneTreeWidget::name).c_str());

    Noctis::Scene *currScene = SCENE_MANAGER().GetCurrScene();

    if (currScene)
    {
        Noctis::ComponentManager &cm = currScene->GetComponentManager();
        
        ImGuiTreeNodeFlags headerFlags = ImGuiTreeNodeFlags_DefaultOpen
            | ImGuiTreeNodeFlags_OpenOnArrow;

        if (ImGui::CollapsingHeader(currScene->GetName().c_str(), headerFlags))
        {
            if (ImGui::IsItemClicked())
                // Remove currently selected entity
                currScene->SetSelectedEntity(0); 

            HandleActorCreationMenu(nullptr); // Parent is the root
            HandleDragDropTarget(nullptr);

            // Avoid undefined behaviour due vector reallocation
            std::vector<Noctis::Entity> allEntities = currScene->GetAllEntities();
            // Iterate through all the scene's entities to add them to the tree
            for (const auto &entity : allEntities)
            {
                auto transform = cm.GetComponent<Noctis::Transform>(entity);

                if (transform->IsChild()) 
                    continue;

                IterateTransformChildren(transform.get(), entity);
            }      
        }
    }        

    ImGui::End();
    ImGui::PopStyleVar();
}


void SceneTreeWidget::IterateTransformChildren(
    Noctis::Transform *transform, 
    const Noctis::Entity &entity)
{
    Noctis::Scene *currScene = SCENE_MANAGER().GetCurrScene();

    ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_DefaultOpen 
        | ImGuiTreeNodeFlags_OpenOnArrow
        | (transform->HasChildren() ? 0 : ImGuiTreeNodeFlags_Leaf) 
        | (entity == currScene->GetSelectedEntity() ? ImGuiTreeNodeFlags_Selected : 0);

    ImGui::PushID((int)entity.GetID());
    bool open = ImGui::TreeNodeEx(transform->GetActor()->GetName().c_str(), treeFlags);

    // Actor selection
    if (ImGui::IsItemClicked())
        currScene->SetSelectedEntity(entity);

    HandleActorCreationMenu(transform);

    if (ImGui::BeginDragDropSource()) 
    {
        ImGui::SetDragDropPayload("SCENE_TREE", &transform, sizeof(Noctis::Transform *));
        ImGui::EndDragDropSource();
    }

    HandleDragDropTarget(transform);

    if (open)
    {
        // Recursively iterate through all the transform's children
        for (Noctis::Transform *child : transform->GetChildren())
            IterateTransformChildren(child, child->GetActor()->GetEntity());
        
        ImGui::TreePop();
    }

    ImGui::PopID();
}


void SceneTreeWidget::HandleActorCreationMenu(Noctis::Transform *parent)
{
    if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
        ImGui::OpenPopup("SCENE_TREE_CREATE_ACTOR");

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.f, 8.f));
    if (ImGui::BeginPopup("SCENE_TREE_CREATE_ACTOR")) 
    {
        if (ImGui::MenuItem("Empty"))
            ActorCreationHelper::CreateEmpty(parent);

        if (ImGui::BeginMenu("Shapes")) 
        {
            if (ImGui::MenuItem("Cube")) 
                ActorCreationHelper::CreateSimpleShape(CUBE_MODEL_NAME, parent);
            
            if (ImGui::MenuItem("Sphere")) 
                ActorCreationHelper::CreateSimpleShape(SPHERE_MODEL_NAME, parent);

            if (ImGui::MenuItem("Cylindre")) 
                ActorCreationHelper::CreateSimpleShape(CYLINDER_MODEL_NAME, parent);
                
            if (ImGui::MenuItem("Monkey")) 
                ActorCreationHelper::CreateSimpleShape(MONKEY_MODEL_NAME, parent);

            ImGui::EndMenu();    
        }

        if (ImGui::BeginMenu("Lights"))
        {
            if (ImGui::MenuItem("Directional Light"))
                ActorCreationHelper::CreateDirectionalLight(parent);
            
            ImGui::EndMenu();    
        }

        ImGui::EndPopup();
    }
    ImGui::PopStyleVar();
}


void SceneTreeWidget::HandleDragDropTarget(Noctis::Transform *parent)
{    
    if (ImGui::BeginDragDropTarget()) 
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SCENE_TREE"))
        {
            if (payload->DataSize != sizeof(Noctis::Transform *))
            {
                LOG_ERR("Drop payload is not valid.");
                return;
            }

            Noctis::Transform *payloadTransform = *(Noctis::Transform **)payload->Data;
            payloadTransform->SetParent(parent);
        }

        ImGui::EndDragDropTarget();
    } 
}

}
