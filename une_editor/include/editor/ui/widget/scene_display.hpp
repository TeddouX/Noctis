#pragma once
#include <iostream>

#include <engine/window.hpp>
#include <engine/scene/scene_manager.hpp>
#include <engine/rendering/framebuffer.hpp>
#include <engine/rendering/camera.hpp>

#include "widget.hpp"


class SceneDisplayWidget : public IWidget
{
public:
    static constexpr std::string_view name = "Scene";

    SceneDisplayWidget(const Window &window)
        : m_window(window) {};

    void Render() override;

private:
    float         m_aspectRatio = 16.f / 9.f;
    float         m_mouseSensitivity = 7.f;
    float         m_cameraSpeed = 2.5f;
    Camera        m_camera = Camera(glm::vec3(0, 0, 0), m_aspectRatio, 70.f, .01f, 1000.f);
    FrameBuffer   m_frameBuffer;
    const Window &m_window;

    int m_viewportWidth, m_viewportHeight;
    int m_viewportX,     m_viewportY;

    void RenderCurrScene();
    void HandleMouseInput();
    void HandleKeyboardInput();
    void UpdateViewport(int windowWidth, int windowHeight);
};
