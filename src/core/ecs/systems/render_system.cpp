#include "render_system.hpp"


void RenderSystem::Update(const ComponentManager &cm, float dt) const
{
    if (!this->m_camera)
    {
        LOG_ERR("The render system has no camera assigned.");
        return;
    }

    const std::unordered_map<Entity, std::shared_ptr<Transform>> &transforms 
        = cm.GetAllComponents<Transform>();

    for (auto &[entity, transform] : transforms) {
        if (cm.HasComponent<ModelComponent>(entity)) {
            std::shared_ptr<ModelComponent> modelComponent 
                = cm.GetComponent<ModelComponent>(entity);
            
            std::shared_ptr<Material> material 
                = cm.GetComponent<Material>(entity);

            // No model, no need for it to be rendered
            if (!modelComponent)
                continue;
            
            // No material is a problem
            if (!material)
            {
                LOG_ERR("Entity({}) has no material assigned, so it can't be rendered.", entity.GetID());
                continue;
            }

            std::shared_ptr<Shader> shader = material->shader;

            // Just a sanity check at this point
            if (!shader)
            {
                LOG_ERR("Material {} has no shader assigned, so it can't be rendered.", material->name);
                continue;
            }

            // Actually render the model
            shader->Use();
            shader->SetMatrix("Model", transform->GetModelMatrix());
            this->m_camera->SetShaderMatrices(*shader);
            modelComponent->model->Render(*shader);
        }
    }
}


void RenderSystem::SetCamera(Camera *camera)
{
    this->m_camera = camera;
}
