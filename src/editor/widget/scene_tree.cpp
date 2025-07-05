#include "scene_tree.hpp"


void SceneTreeWidget::Render()
{
    ImGui::Begin(std::string(SceneTreeWidget::name).c_str());

    Scene *currScene = SCENE_MANAGER().GetCurrScene();

    if (currScene)
    {
        ComponentManager &cm = currScene->GetComponentManager();
        
        for (const Entity &entity : currScene->GetAllEntities())
        {
            Transform &transform = *cm.GetComponent<Transform>(entity);

            if (transform.IsChild()) 
                continue;

            std::string name = transform.GetActor()->GetName();
            if (name.empty())
                name = "Default Actor";

            if (!transform.HasChildren())
            {
                ImGui::Text(name.c_str()); 
                continue;
            }

            
            if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                this->IterateActorChildren(transform);
                ImGui::TreePop();
            } 
        }   
    }        

    ImGui::End();
}


void SceneTreeWidget::IterateActorChildren(const Transform &transform)
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
}
