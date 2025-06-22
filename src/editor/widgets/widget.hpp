#pragma once
#include <imgui.h>


class Widget
{
public:
    Widget() = default;

    virtual void Render() {};
    virtual void Update() {};
};
