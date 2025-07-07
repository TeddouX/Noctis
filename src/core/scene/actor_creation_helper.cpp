#include "actor_creation_helper.hpp"
#include "../asset_manager.hpp"


void ActorCreationHelper::CreateEmpty(Transform *parent)
{
    Scene *currScene = SCENE_MANAGER().GetCurrScene();
    ComponentManager &cm = currScene->GetComponentManager();
    
    Entity entity = Entity::Create();
    std::shared_ptr<Actor> actor = std::make_shared<Actor>("Empty Actor", entity);
    cm.AddComponent(entity, actor);
    cm.AddComponent(entity, std::make_shared<Transform>(
        glm::vec3(0), // 0, 0, 0
        glm::vec3(0), // No rotation 
        parent ? glm::vec3(0) : glm::vec3(1), // Because scale is also relative to the parent 
        actor, 
        parent
    ));

    currScene->AddEntity(entity);

    LOG_INFO("Created empty actor.")
}


void ActorCreationHelper::CreateSimpleShape(EmbeddedModel modelType, Transform *parent)
{
    Scene *currScene = SCENE_MANAGER().GetCurrScene();
    ComponentManager &cm = currScene->GetComponentManager();
    AssetManager &am = PROJECT()->GetAssetManager();
    
    Entity entity = Entity::Create();
    std::shared_ptr<Model> model = am.GetEmbeddedModel(modelType);
    std::shared_ptr<Actor> actor = std::make_shared<Actor>(model->GetName(), entity);
    cm.AddComponent(entity, actor);
    cm.AddComponent(entity, std::make_shared<Transform>(
        glm::vec3(0), // 0, 0, 0
        glm::vec3(0), // No rotation 
        parent ? glm::vec3(0) : glm::vec3(1), // Because scale is also relative to the parent 
        actor, 
        parent
    ));
    cm.AddComponent(entity, std::make_shared<ModelComponent>(*model));

    std::shared_ptr<Shader> shader = am.GetEmbeddedShader(EmbeddedShader::DEFAULT);
    cm.AddComponent(entity, std::make_shared<Material>("default", shader));

    currScene->AddEntity(entity);

    LOG_INFO("Created an actor with model ({})", model->GetName())
}
