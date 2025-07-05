#include <imgui.h>
#include "imgui_utils.hpp"


namespace ImGui
{

bool ResizableInputText(const char* label, std::string& str)
{
    // Prevent the buffer from pointing to null
    if (str.empty())
        str.resize(1);

    bool changed = ImGui::InputText(
        label, 
        &str[0], 
        str.capacity(),
        ImGuiInputTextFlags_CallbackResize,
        [](ImGuiInputTextCallbackData* data) -> int
        {
            if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
            {
                // This is the last argument passed into ImGui::InputText
                std::string* str = static_cast<std::string*>(data->UserData);
                // Remove the null terminator from the ImGui input
                str->resize(data->BufSize - 1);
                // Replace buffer
                data->Buf = &(*str)[0];
            }
            return 0;
        },
        (void*)&str
    );

    // Resize to the correct visible size
    str.resize(std::strlen(str.c_str()));

    return changed;
}

void InlinedLabel(const char* text)
{
    ImGui::Text(text);
    ImGui::SameLine();
    ImGui::SetCursorPosX(64.f);
}

} // namespace ImGui
