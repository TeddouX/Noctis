#include "render_system.hpp"


void RenderSystem::Update(const ComponentManager &cm, float dt)
{
    if (!this->m_camera)
    {
        LOG_ERR("The render system has no camera assigned.")
        return;
    }

    const auto &models = cm.GetEntities<ModelComponent>();

    glClearColor(.09f, .09f, .09f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto &[entity, model] : models) {
        auto transform = cm.GetComponent<Transform>(entity);
        auto material = cm.GetComponent<Material>(entity);
        
        // No material is a problem
        if (!material)
        {
            LOG_ERR("Entity({}) has no material assigned, so it can't be rendered.", entity.GetID())
            continue;
        }

        std::shared_ptr<Shader> shader = material->GetShader();

        // Just a sanity check at this point
        if (!shader)
        {
            LOG_ERR("Material {} has no shader assigned, so it can't be rendered.", material->GetName())
            continue;
        }

        // Actually render the model
        shader->Use();
        material->UploadData();
        this->m_camera->UploadData(transform->GetModelMatrix());
        model->GetModel()->Render(*shader);
    }
}


void RenderSystem::SetCamera(Camera *camera)
{
    this->m_camera = camera;
}
