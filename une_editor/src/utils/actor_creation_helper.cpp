#include "utils/actor_creation_helper.hpp"


void ActorCreationHelper::AddDefaultComponents(
    ComponentManager &cm, 
    Entity entity, 
    Transform *parent, 
    const std::string &name
)
{
    Actor actor(name, entity);
    cm.AddComponent(entity, actor);
    cm.AddComponent(entity, Transform(
        Vec3(0), // 0, 0, 0
        Vec3(0), // No rotation 
        parent ? Vec3(0) : Vec3(1), // Because scale is also relative to the parent 
        std::make_shared<Actor>(actor), 
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

    cm.AddComponent(entity, ModelComponent(model));

    std::shared_ptr<Shader> shader = am.GetShader(std::string(LIT_SHADER_NAME));
    cm.AddComponent(entity, Material("default", shader));

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

    cm.AddComponent(entity, DirectionalLight(
        Color::White(), 
        Color::White(), 
        Color::White()
    ));
    
    currScene->AddEntity(entity);    
    currScene->SetSelectedEntity(entity);
    
    LOG_INFO("Created a directional light")
}
