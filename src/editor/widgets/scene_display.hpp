#pragma once
#include <iostream>

#include "../../rendering/framebuffer.hpp"
#include "widget.hpp"


class SceneDisplayWidget : public IWidget
{
public:
    static constexpr std::string_view name = "Scene";

    SceneDisplayWidget();

    void Render() override;

private:
    FrameBuffer m_frameBuffer = FrameBuffer(0, 0);
};
