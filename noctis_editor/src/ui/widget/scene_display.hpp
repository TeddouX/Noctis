#pragma once
#include <noctis/window.hpp>
#include <noctis/rendering/framebuffer.hpp>
#include <noctis/rendering/camera.hpp>

#include "widget.hpp"

namespace NoctisEditor
{

class SceneDisplayWidget : public IWidget
{
public:
    SceneDisplayWidget(std::shared_ptr<Noctis::Window> window)
        : m_window(window) {};

    static std::string GetName() { return "Scene"; }

    void Render() override;

private:
    float       m_aspectRatio = 16.f / 9.f;
    float       m_mouseSensitivity = 7.f;
    float       m_cameraSpeed = 2.5f;

    Noctis::Camera m_camera = Noctis::Camera(
        Noctis::Vec3(0), 
        m_aspectRatio, 
        70.f, 
        .01f, 1000.f
    );

    std::shared_ptr<Noctis::Window> m_window;
    Noctis::FrameBuffer m_frameBuffer;

    int m_viewportWidth, m_viewportHeight;
    int m_viewportX,     m_viewportY;

    void RenderCurrScene();
    void HandleMouseInput();
    void HandleKeyboardInput();
    void UpdateViewport(int windowWidth, int windowHeight);
};

}
