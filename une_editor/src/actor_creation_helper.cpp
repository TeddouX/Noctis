#include "actor_creation_helper.hpp"


void ActorCreationHelper::AddDefaultComponents(
    ComponentManager &cm, 
    Entity entity, 
    Transform *parent, 
    const std::string &name
)
{
    std::shared_ptr<Actor> actor = std::make_shared<Actor>(name, entity);
    cm.AddComponent(entity, actor);
    cm.AddComponent(entity, std::make_shared<Transform>(
        glm::vec3(0), // 0, 0, 0
        glm::vec3(0), // No rotation 
        parent ? glm::vec3(0) : glm::vec3(1), // Because scale is also relative to the parent 
        actor, 
        parent
    ));
}


void ActorCreationHelper::CreateEmpty(Transform *parent)
{
    Scene *currScene = SCENE_MANAGER().GetCurrScene();
    ComponentManager &cm = currScene->GetComponentManager();
    
    Entity entity = Entity::Create();
    
    AddDefaultComponents(cm, entity, parent, "Empty Actor");

    currScene->AddEntity(entity);
    currScene->SetSelectedEntity(entity);

    LOG_INFO("Created an empty actor")
}


void ActorCreationHelper::CreateSimpleShape(std::string_view modelName, Transform *parent)
{
    Scene *currScene = SCENE_MANAGER().GetCurrScene();
    ComponentManager &cm = currScene->GetComponentManager();
    AssetManager &am = AssetManager::GetInstance();
    
    Entity entity = Entity::Create();
    std::shared_ptr<Model> model = am.GetModel(std::string(modelName));
    
    AddDefaultComponents(cm, entity, parent, model->GetBeautifiedName());

    cm.AddComponent(entity, std::make_shared<ModelComponent>(model));

    std::shared_ptr<Shader> shader = am.GetShader(std::string(LIT_SHADER_NAME));
    cm.AddComponent(entity, std::make_shared<Material>("default", shader));

    currScene->AddEntity(entity);
    currScene->SetSelectedEntity(entity);

    LOG_INFO("Created an actor with model ({})", model->GetBeautifiedName())
}


void ActorCreationHelper::CreateDirectionalLight(Transform *parent)
{
    Scene *currScene = SCENE_MANAGER().GetCurrScene();
    ComponentManager &cm = currScene->GetComponentManager();

    Entity entity = Entity::Create();

    AddDefaultComponents(cm, entity, parent, "Directional Light");

    cm.AddComponent(entity, std::make_shared<DirectionalLight>(
        Color::White(), 
        Color::White(), 
        Color::White()
    ));
    
    currScene->AddEntity(entity);    
    currScene->SetSelectedEntity(entity);
    
    LOG_INFO("Created a directional light")
}
