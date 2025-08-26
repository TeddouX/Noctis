#pragma once
#include <string>
#include <imgui.h>

#include <engine/math/color.hpp>


namespace NoctisEditor
{

void ResizableInputText(const char* label, std::string& str, bool needsEnter);
void InlinedLabel(const char* text);
void ColorEditEx(
    const char* label, 
    Noctis::Color &color, 
    ImGuiColorEditFlags flags = 0
);

}