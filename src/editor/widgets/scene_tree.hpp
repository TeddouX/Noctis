#pragma once
#include "widget.hpp"


class SceneTreeWidget : public IWidget
{
public:
    static constexpr std::string_view name = "Scene Tree";

    void Render() override;
};
