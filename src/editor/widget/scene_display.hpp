#pragma once
#include <iostream>

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
    Camera      m_camera = Camera(glm::vec3(-3, 0, 0), glm::vec2(0, 0), 60.f, .01f, 1000.f);
    FrameBuffer m_frameBuffer;
};
