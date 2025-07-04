#pragma once
#include "system.hpp"
#include "../components/model_component.hpp"
#include "../components/transform.hpp"
#include "../components/material.hpp"
#include "../component_manager.hpp"
#include "../entity.hpp"
#include "../../../rendering/camera.hpp"
#include "../../../rendering/model.hpp"
#include "../../../rendering/shader.hpp"


class RenderSystem : public ISystem 
{
public:
    void Update(const ComponentManager &cm, float dt) const override;

    void SetCamera(Camera *camera);

private:
    Camera *m_camera;
};
