#include "scene_tree.hpp"


void SceneTreeWidget::Render()
{
    ImGui::Begin(std::string(SceneTreeWidget::name).c_str());

    Scene *currScene = SCENE_MANAGER().GetCurrScene();
    ComponentManager &cm = currScene->GetComponentManager();

    if (currScene)
    {
        for (const Entity &entity : currScene->GetAllEntities())
        {
            Actor actor = *cm.GetComponent<Actor>(entity);

            if (actor.IsChild()) continue;

            if (!actor.HasChildren())
            {
                ImGui::Text(actor.name.c_str()); 
                continue;
            }

            if (ImGui::TreeNode(actor.name.c_str()))
            {
                this->IterateActorChildren(actor);
                ImGui::TreePop();
            } 
        }   
    }        

    ImGui::End();
}


void SceneTreeWidget::IterateActorChildren(const Actor &actor)
{
    for (Actor *childActor : actor.GetChildren())
    {
        if (!childActor->HasChildren())
        {
            ImGui::Text(childActor->name.c_str()); 
            continue;
        }

        if (ImGui::TreeNode(childActor->name.c_str()))
        {
            this->IterateActorChildren(*childActor);
            ImGui::TreePop();
        }
    }
}
