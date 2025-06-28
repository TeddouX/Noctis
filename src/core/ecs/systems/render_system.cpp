#include "render_system.hpp"


void RenderSystem::Update(const ComponentManager &cm, float dt) const
{
    const std::unordered_map<Entity, TransformComponent> &transforms 
        = cm.GetAllComponents<TransformComponent>();

    for (auto &[entity, transform] : transforms) {
        if (cm.HasComponent<ModelComponent>(entity)) {
            ModelComponent& modelComponent = cm.GetComponent<ModelComponent>(entity);

            Renderer::RenderModel(*modelComponent.model, transform);
        }
    }
}
