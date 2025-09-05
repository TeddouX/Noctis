#include "scene_manager.hpp"

#include <noctis/ecs/system/lighting_system.hpp>
#include <noctis/ecs/system/render_system.hpp>$

#include "editor.hpp"

namespace NoctisEditor
{
    
void SceneManager::AddScene(const fs::path &scenePath)
{
    std::string name = scenePath.stem().string();
    Noctis::Scene scene(name);
    AddEditorSystems(scene);

    m_scenes.emplace(name, scene);
}

void SceneManager::CreateScene(const std::string &name)
{
    Noctis::Scene scene(name);
    AddEditorSystems(scene);

    Noctis::Filesystem::WriteBytes(
        GetScenePath(name), 
        nlohmann::json::to_cbor(nlohmann::json())
    );

    m_scenes.emplace(name, scene);
}

void SceneManager::RemoveScene(const std::string &name)
{
    if (m_scenes.contains(name))
        m_scenes.erase(name);
    else
        LOG_ERR("Scene {} couldn't be deleted as it isn't registered");
}

void SceneManager::SaveCurrentScene()
{
    if (m_currScene)
    {
        nlohmann::json sceneJson = m_currScene->Serialize();

        std::vector<uint8_t> cborBytes = nlohmann::json::to_cbor(sceneJson);
        Noctis::Filesystem::WriteBytes(m_currScenePath, cborBytes);
    }
}

void SceneManager::SetCurrentScene(const std::string &name)
{
    if (m_scenes.contains(name))
    {
        if (m_currScene)
        {
            m_currScene->Unload();
            Editor::GetInstance().GetCurrProject()->SetSelectedEntity(Noctis::Entity());
        }

        m_currScene = &m_scenes.at(name);
        m_currScenePath = GetScenePath(name);

        std::vector<uint8_t> cborBytes = Noctis::Filesystem::ReadBytes(m_currScenePath);
        nlohmann::json sceneJson = nlohmann::json();

        if (cborBytes.size() != 0)
            sceneJson = nlohmann::json::from_cbor(cborBytes);

        m_currScene->Load(sceneJson);
    }
    else
        LOG_ERR("Scene {} doesn't exist.");
}

fs::path SceneManager::GetScenePath(const std::string &name) const
{
    return m_scenesFolder / (name + ".scene");
}

void SceneManager::AddEditorSystems(Noctis::Scene &scene)
{
    Noctis::SystemsManager &sm = scene.GetSystemsManager();

    sm.RegisterSystem<Noctis::LightingSystem>();
    sm.RegisterSystem<Noctis::RenderSystem>();
}

void SceneManager::AddRuntimeSystems(Noctis::Scene& scene)
{

}

} // namespace NoctisEditor
