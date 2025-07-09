#include "lighting_system.hpp"


void LightingSystem::Update(const ComponentManager &cm, float dt)
{
    const std::unordered_map<Entity, std::shared_ptr<DirectionalLight>> dirLightsMap
        = cm.GetEntities<DirectionalLight>();

    for (auto &[entity, dirLight] : dirLightsMap)
        dirLight->rotation = cm.GetComponent<Transform>(entity)->GetWorldRot();

    std::vector<DirectionalLight::Data> dirLightsData;
    for (DirectionalLight dirLight : GetAllValues(dirLightsMap))
        dirLightsData.push_back(dirLight.GetData());

    this->UploadLights(dirLightsData, this->m_dirLightSSBO);
}
