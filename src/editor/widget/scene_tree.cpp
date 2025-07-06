#include "scene_tree.hpp"


void SceneTreeWidget::Render()
{
    ImGui::Begin(std::string(SceneTreeWidget::name).c_str());

    Scene *currScene = SCENE_MANAGER().GetCurrScene();

    if (currScene)
    {
        ComponentManager &cm = currScene->GetComponentManager();
        
        if (ImGui::CollapsingHeader(currScene->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
        {
            // Set parent to the scene root
            if (ImGui::BeginDragDropTarget()) 
            {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SCENE_TREE"))
                {
                    if (payload->DataSize != sizeof(Transform *))
                    {
                        LOG_ERR("Drop payload is not valid.")
                        return;
                    }

                    Transform *payloadTransform = *(Transform **)payload->Data;
                    payloadTransform->SetParent(nullptr);
                }

                ImGui::EndDragDropTarget();
            }

            for (const Entity *entity : currScene->GetAllEntities())
            {
                std::shared_ptr<Transform> transform = cm.GetComponent<Transform>(*entity);

                if (transform->IsChild()) 
                    continue;

                IterateTransformChildren(transform.get(), entity);
            }      
        }
    }        

    ImGui::End();
}


void SceneTreeWidget::IterateTransformChildren(Transform *transform, const Entity *entity)
{
    Scene *currScene = SCENE_MANAGER().GetCurrScene();

    ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_DefaultOpen 
        | ImGuiTreeNodeFlags_OpenOnArrow
        | (transform->HasChildren() ? 0 : ImGuiTreeNodeFlags_Leaf) 
        | (entity == currScene->GetSelectedEntity() ? ImGuiTreeNodeFlags_Selected : 0);

    bool open = ImGui::TreeNodeEx(transform->GetActor()->GetName().c_str(), treeFlags);

    if (ImGui::IsItemClicked())
        currScene->SetSelectedEntity(entity);


    if (ImGui::BeginDragDropSource()) 
    {
        ImGui::SetDragDropPayload("SCENE_TREE", &transform, sizeof(Transform *));
        ImGui::EndDragDropSource();
    }
    
    if (ImGui::BeginDragDropTarget()) 
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SCENE_TREE"))
        {
            if (payload->DataSize != sizeof(Transform *))
            {
                LOG_ERR("Drop payload is not valid.")
                return;
            }

            Transform *payloadTransform = *(Transform **)payload->Data;
            payloadTransform->SetParent(transform);
        }

        ImGui::EndDragDropTarget();
    }  

    if (open)
    {
        for (Transform *child : transform->GetChildren())
            IterateTransformChildren(child, child->GetActor()->GetEntity());
        
        ImGui::TreePop();
    }
}
