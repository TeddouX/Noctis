#include "imgui_utils.hpp"


namespace NoctisEditor
{

void ResizableInputText(const char* label, std::string& str, bool needsEnter)
{
    // Prevent the buffer from pointing to null
    std::string buf = str;
    if (buf.empty())
    buf.resize(1);

    ImGuiInputFlags flags = ImGuiInputTextFlags_CallbackResize
        | (needsEnter ? ImGuiInputTextFlags_EnterReturnsTrue : 0);

    if (ImGui::InputText(
        label, 
        (char *)str.c_str(), 
        buf.capacity(), 
        flags,
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
    ImGui::SetCursorPosX(ImGui::CalcTextSize(text).x + 64.f);
}


void ColorEditEx(const char* label, Noctis::Color &color, ImGuiColorEditFlags flags)
{
    ImVec4 colorVec = ImVec4(color.GetRed() / 255.f, color.GetGreen() / 255.f, color.GetBlue() / 255.f, 0.f);

    if (ImGui::ColorEdit3(label, (float *)&colorVec, flags))
    {
        color.SetRed((uint8_t)(colorVec.x * 255));
        color.SetGreen((uint8_t)(colorVec.y * 255));
        color.SetBlue((uint8_t)(colorVec.z * 255));
    }
}


bool ClickableText(const char *text)
{
    ImGui::Text(text);

    if (ImGui::IsItemHovered())
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

    return ImGui::IsItemClicked(ImGuiMouseButton_Left);
}

}
