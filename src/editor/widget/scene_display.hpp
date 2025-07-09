#pragma once
#include <iostream>

#include "../../core/scene/scene_manager.hpp"
#include "../../rendering/framebuffer.hpp"
#include "../../rendering/camera.hpp"
#include "widget.hpp"


class SceneDisplayWidget : public IWidget
{
public:
    static constexpr std::string_view name = "Scene";

    SceneDisplayWidget();

    void Render() override;

private:
    float       m_aspectRatio = 16.f / 9.f;
    Camera      m_camera = Camera(glm::vec3(-3, 0, 0), m_aspectRatio, 70.f, .01f, 1000.f);
    FrameBuffer m_frameBuffer;

    int m_viewportWidth, m_viewportHeight;
    int m_viewportX, m_viewportY;

    void UpdateViewport(int windowWidth, int windowHeight);
};
