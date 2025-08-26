#pragma once
#include <string>
#include <imgui.h>

namespace NoctisEditor
{

class IWidget
{
public:
    IWidget() = default;

    virtual void Render() {};
    virtual void Update() {};
};

}
