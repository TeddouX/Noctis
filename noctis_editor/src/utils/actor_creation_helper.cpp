#include "actor_creation_helper.hpp"

#include <engine/asset/asset_manager.hpp>
#include <engine/scene/scene_manager.hpp>
#include <engine/ecs/component/model_component.hpp>
#include <engine/ecs/component/actor_component.hpp>
#include <engine/ecs/component/material_component.hpp>
#include <engine/ecs/component/light_component.hpp>

namespace NoctisEditor
{

void ActorCreationHelper::AddDefaultComponents( 
    Noctis::Entity entity, 
    Noctis::Transform *parent, 
    const std::string &name
)
{
    auto actor = std::make_shared<Noctis::Actor>(name, entity);
    entity.AddComponent(actor);
    entity.AddComponent(std::make_shared<Noctis::Transform>(
        Noctis::Vec3(0), // 0, 0, 0
        Noctis::Vec3(0), // No rotation 
        parent ? Noctis::Vec3(0) : Noctis::Vec3(1), // Because scale is also relative to the parent 
        actor, 
        parent
    ));
}


void ActorCreationHelper::CreateEmpty(Noctis::Transform *parent)
{
    Noctis::Scene *currScene = SCENE_MANAGER().GetCurrScene();
    
    Noctis::Entity entity(&currScene->GetComponentManager());
    
    AddDefaultComponents(entity, parent, "Empty Actor");

    currScene->AddEntity(entity);
    currScene->SetSelectedEntity(entity);

    LOG_INFO("Created an empty actor");
}


void ActorCreationHelper::CreateSimpleShape(
    std::string_view modelName, 
    Noctis::Transform *parent)
{
    Noctis::Scene *currScene = SCENE_MANAGER().GetCurrScene();
    Noctis::IAssetManager *am = Noctis::AssetManagerAccessor::Get();
    
    Noctis::Entity entity(&currScene->GetComponentManager());
    auto model = am->GetTyped<Noctis::Model>(
        Noctis::AssetType::MODEL, 
        std::string(modelName)
    );
    
    AddDefaultComponents(entity, parent, model->Name);

    entity.AddComponent(std::make_shared<Noctis::ModelComponent>(model));

    auto shader = am->GetTyped<Noctis::Shader>(
        Noctis::AssetType::SHADER, 
        std::string(LIT_SHADER_NAME)
    );
    entity.AddComponent(std::make_shared<Noctis::Material>("default", shader));

    currScene->AddEntity(entity);
    currScene->SetSelectedEntity(entity);

    LOG_INFO("Created an actor with model ({})", model->Name);
}


void ActorCreationHelper::CreateDirectionalLight(Noctis::Transform *parent)
{
    Noctis::Scene *currScene = SCENE_MANAGER().GetCurrScene();

    Noctis::Entity entity(&currScene->GetComponentManager());

    AddDefaultComponents(entity, parent, "Directional Light");

    entity.AddComponent(std::make_shared<Noctis::DirectionalLight>(
        Noctis::Color::White(), 
        Noctis::Color::White(), 
        Noctis::Color::White()
    ));
    
    currScene->AddEntity(entity);    
    currScene->SetSelectedEntity(entity);
    
    LOG_INFO("Created a directional light");
}

}
