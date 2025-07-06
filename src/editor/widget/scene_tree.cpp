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
            for (const Entity &entity : currScene->GetAllEntities())
            {
                Transform &transform = *cm.GetComponent<Transform>(entity);

                if (transform.IsChild()) 
                    continue;

                if (!transform.HasChildren())
                {
                    ImGui::Text(transform.GetActor()->GetName().c_str()); 
                    continue;
                }

                this->IterateActorChildren(transform);
            }      
        }
    }        

    ImGui::End();
}


void SceneTreeWidget::IterateActorChildren(const Transform &transform)
{
    if (ImGui::TreeNodeEx(transform.GetActor()->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
    {
        for (Transform *childTransform : transform.GetChildren())
    {
        if (!childTransform->HasChildren())
        {
            ImGui::Text(childTransform->GetActor()->GetName().c_str()); 
            continue;
        }


        if (ImGui::TreeNode(childTransform->GetActor()->GetName().c_str()))
        {
            this->IterateActorChildren(*childTransform);
            ImGui::TreePop();
        }
    }


        ImGui::TreePop();
    }
}
