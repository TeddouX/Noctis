#pragma once
#include <iostream>
#include <glm/glm.hpp>

#include "../../rendering/framebuffer.hpp"
#include "widget.hpp"


class SceneDisplayWidget : public Widget
{
public:
    static constexpr std::string_view name = "SceneDisplay";

    SceneDisplayWidget();

    void Render() override;

private:
    FrameBuffer m_frameBuffer = FrameBuffer(0, 0);
};
