#include "ecs/system/lighting_system.hpp"


void LightingSystem::Update(ComponentManager &cm, float dt)
{
    auto &dirLightsMap = cm.GetEntitiesWith<DirectionalLight>();

    for (auto &[entity, dirLight] : dirLightsMap)
        dirLight->SetRotation(entity.GetComponent<Transform>()->GetWorldRot());

    std::vector<DirectionalLight::Data> dirLightsData;
    for (auto dirLight : GetAllValues(dirLightsMap))
        dirLightsData.push_back(dirLight->GetData());

    this->UploadLights(dirLightsData, this->m_dirLightSSBO);
}
