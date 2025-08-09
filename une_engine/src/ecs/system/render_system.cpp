#include "ecs/system/render_system.hpp"


void RenderSystem::Update(ComponentManager &cm, float dt)
{
    if (!this->m_camera)
    {
        LOG_ERR("The render system has no camera assigned.");
        return;
    }

    auto &models = cm.GetEntitiesWith<ModelComponent>();

    glClearColor(.09f, .09f, .09f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto &[entity, model] : models) 
    {
        auto transform = entity.GetComponent<Transform>();
        auto material = entity.GetComponent<Material>();
        
        // No material is a problem
        if (!material)
        {
            LOG_ERR("Entity({}) has no material assigned, so it can't be rendered.", entity.GetID());
            continue;
        }

        auto shader = material->GetShader();

        // Just a sanity check at this point
        if (!shader)
        {
            LOG_ERR("Material {} has no shader assigned, so it can't be rendered.", material->GetName());
            continue;
        }

        // Actually render the model
        shader->Use();
        material->UploadData(*shader);
        this->m_camera->UploadData();
        model.GetModel()->Render(*shader, transform->GetModelMatrix());
    }
}


void RenderSystem::SetCamera(Camera *camera)
{
    this->m_camera = camera;
}
