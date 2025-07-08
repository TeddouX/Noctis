#include <string>
#include <imgui.h>
#include "math/color.hpp"


namespace ImGui
{

extern void ResizableInputText(const char* label, std::string& str);
extern void InlinedLabel(const char* text);
extern void ColorEditEx(const char* label, Color &color, ImGuiColorEditFlags flags = 0);

}