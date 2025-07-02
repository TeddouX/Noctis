#pragma once
#include <string>

#include <imgui.h>


class IWidget
{
public:
    IWidget() = default;

    virtual void Render() {};
    virtual void Update() {};
};
