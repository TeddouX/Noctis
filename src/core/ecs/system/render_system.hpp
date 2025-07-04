#pragma once
#include "system.hpp"
#include "../component/model_component.hpp"
#include "../component/transform.hpp"
#include "../component/material.hpp"
#include "../component_manager.hpp"
#include "../entity.hpp"
#include "../../../rendering/camera.hpp"
#include "../../../rendering/model.hpp"
#include "../../../rendering/shader.hpp"


// This system renders object to the screen
class RenderSystem : public ISystem 
{
public:
    void Update(const ComponentManager &cm, float dt) const override;

    // Set the camera used for drawing
    void SetCamera(Camera *camera);

private:
    Camera *m_camera;
};
