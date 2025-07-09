#include "scene.hpp"


Scene::Scene(const std::string &name)
    : m_name(name)
{
    // Register all systems
    this->m_systemsManager.RegisterSystem<RenderSystem>();
    this->m_systemsManager.RegisterSystem<LightingSystem>();
}


void Scene::RemoveEntity(Entity entity)
{
    this->m_sceneEntities.erase(
        std::remove(
            this->m_sceneEntities.begin(), 
            this->m_sceneEntities.end(), 
            entity
        ), 
        this->m_sceneEntities.end()
    );
}


void Scene::UpdateAllSystems(float dt)
{
    this->m_systemsManager.UpdateAll(this->m_componentManager, dt); 
}


void Scene::Load()
{
    std::string jsonPath = fmt::format(
        "{}\\{}.json", 
        PROJECT()->GetScenesFolder(), 
        this->m_name
    );

    if (!fs::exists(jsonPath))
    {
        LOG_WARN(
            "The JSON file ({}) for scene {} doesn't exist. Creating one now...", 
            jsonPath, 
            this->m_name
        )
        // Empty for now
        json j({});
        std::string jsonStr = j.dump();

        // Create JSON file
        std::ofstream jsonFile(jsonPath);

        jsonFile << jsonStr;

        jsonFile.close();

        return;
    }

    LOG_TODO("Continue Scene::Load() implementation.")
    // LOG_INFO("Loaded scene {}.", this->m_name);
}


void Scene::Unload()
{
    LOG_TODO("Scene::Unload() implementation.")
}
