#include "actor_creation_helper.hpp"

#include <engine/asset_manager.hpp>
#include <engine/scene/scene_manager.hpp>
#include <engine/ecs/component/model_component.hpp>
#include <engine/ecs/component/actor_component.hpp>
#include <engine/ecs/component/material_component.hpp>
#include <engine/ecs/component/light_component.hpp>


void ActorCreationHelper::AddDefaultComponents( 
    Entity entity, 
    Transform *parent, 
    const std::string &name
)
{
    Actor actor(name, entity);
    entity.AddComponent(actor);
    entity.AddComponent(Transform(
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
    
    Entity entity(&currScene->GetComponentManager());
    
    AddDefaultComponents(entity, parent, "Empty Actor");

    currScene->AddEntity(entity);
    currScene->SetSelectedEntity(entity);

    LOG_INFO("Created an empty actor");
}


void ActorCreationHelper::CreateSimpleShape(std::string_view modelName, Transform *parent)
{
    Scene *currScene = SCENE_MANAGER().GetCurrScene();
    AssetManager &am = AssetManager::GetInstance();
    
    Entity entity(&currScene->GetComponentManager());
    std::shared_ptr<Model> model = am.GetModel(std::string(modelName));
    
    AddDefaultComponents(entity, parent, model->GetBeautifiedName());

    entity.AddComponent(ModelComponent(model));

    std::shared_ptr<Shader> shader = am.GetShader(std::string(LIT_SHADER_NAME));
    entity.AddComponent(Material("default", shader));

    currScene->AddEntity(entity);
    currScene->SetSelectedEntity(entity);

    LOG_INFO("Created an actor with model ({})", model->GetBeautifiedName());
}


void ActorCreationHelper::CreateDirectionalLight(Transform *parent)
{
    Scene *currScene = SCENE_MANAGER().GetCurrScene();

    Entity entity(&currScene->GetComponentManager());

    AddDefaultComponents(entity, parent, "Directional Light");

    entity.AddComponent(DirectionalLight(
        Color::White(), 
        Color::White(), 
        Color::White()
    ));
    
    currScene->AddEntity(entity);    
    currScene->SetSelectedEntity(entity);
    
    LOG_INFO("Created a directional light");
}
