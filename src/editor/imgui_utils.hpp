#include <string>
#include <imgui.h>

#include "../core/math/color.hpp"


namespace ImGui
{

void ResizableInputText(const char* label, std::string& str);
void InlinedLabel(const char* text);
void ColorEditEx(const char* label, Color &color, ImGuiColorEditFlags flags = 0);

}