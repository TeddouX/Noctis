#pragma once
#include "system.hpp"
#include "../entity.hpp"
#include "../component/model_component.hpp"
#include "../component/transform_component.hpp"
#include "../component/material_component.hpp"
#include "../component_manager.hpp"
#include "../../rendering/camera.hpp"
#include "../../rendering/model.hpp"
#include "../../rendering/shader.hpp"


// This system renders object to the screen
class NOCTIS_API RenderSystem : public ISystem 
{
public:
    void Update(ComponentManager &cm, float dt) override;

    // Set the camera used for drawing
    void SetCamera(Camera *camera);

private:
    Camera *m_camera;
};
