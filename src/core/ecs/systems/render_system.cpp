#include "render_system.hpp"


void RenderSystem::Update(const ComponentManager &cm, float dt) const
{
    const std::unordered_map<Entity, std::shared_ptr<Transform>> &transforms 
        = cm.GetAllComponents<Transform>();

    for (auto &[entity, transform] : transforms) {
        if (cm.HasComponent<ModelComponent>(entity)) {
            ModelComponent modelComponent = *cm.GetComponent<ModelComponent>(entity);

            Renderer::RenderModel(*modelComponent.model, *transform);
        }
    }
}
