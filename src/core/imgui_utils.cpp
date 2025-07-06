#include <imgui.h>
#include "imgui_utils.hpp"


namespace ImGui
{

void ResizableInputText(const char* label, std::string& str)
{
    // Prevent the buffer from pointing to null
    std::string buf = str;
    if (buf.empty())
        buf.resize(1);

    if (ImGui::InputText(
        label, 
        &buf[0], 
        buf.capacity(),
        ImGuiInputTextFlags_CallbackResize | ImGuiInputTextFlags_EnterReturnsTrue,
        [](ImGuiInputTextCallbackData* data) -> int
        {
            if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
            {
                // This is the last argument passed into ImGui::InputText
                std::string* buf = static_cast<std::string*>(data->UserData);
                // Remove the null terminator from the ImGui input
                buf->resize(data->BufSize - 1);
                // Replace buffer
                data->Buf = &(*buf)[0];
            }
            return 0;
        },
        (void*)&buf
    ))
    {
        // Resize to the correct visible size
        buf.resize(std::strlen(buf.c_str()));
        str = buf;
    }
}

void InlinedLabel(const char* text)
{
    ImGui::Text(text);
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::CalcTextSize(text).x + 48.f);
}

} // namespace ImGui
