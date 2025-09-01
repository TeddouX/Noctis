#include "property_rendering.hpp"

#include <imgui.h>
#include <noctis/property/asset_property.hpp>
#include <noctis/property/color_property.hpp>
#include <noctis/property/float_property.hpp>
#include <noctis/property/int_property.hpp>
#include <noctis/property/string_property.hpp>
#include <noctis/property/vec3_property.hpp>

#include "imgui_utils.hpp"

namespace NoctisEditor
{

std::string GenImGuiID(
    std::string prefix, 
    std::shared_ptr<Noctis::IPropertyBase> property, 
    std::shared_ptr<Noctis::IPropertyHolder> component
);


template <>
void RenderProperty(
    std::shared_ptr<Noctis::IntProperty> prop, 
    std::shared_ptr<Noctis::IPropertyHolder> propHolder)
{
    NoctisEditor::InlinedLabel(prop->GetName().c_str());

    int &i = prop->GetValue();
    ImGui::DragInt(
        GenImGuiID("int_input", prop, propHolder).c_str(), 
        &i, 
        (float)prop->stepSize, 
        prop->minVal, prop->maxVal
    );
}


template <>
void RenderProperty(
    std::shared_ptr<Noctis::FloatProperty> prop, 
    std::shared_ptr<Noctis::IPropertyHolder> propHolder)
{
    NoctisEditor::InlinedLabel(prop->GetName().c_str());

    float &f = prop->GetValue();
    ImGui::DragFloat(GenImGuiID("int_input", prop, propHolder).c_str(), 
        &f, 
        prop->stepSize, 
        prop->minVal, prop->maxVal
    );
}


template <>
void RenderProperty(
    std::shared_ptr<Noctis::Vec3Property> prop, 
    std::shared_ptr<Noctis::IPropertyHolder> propHolder)
{
    NoctisEditor::InlinedLabel(prop->GetName().c_str());

    Noctis::Vec3 &v3 = prop->GetValue();
    std::string id = GenImGuiID("vec3_input", prop, propHolder);

    ImGui::PushItemWidth(64.f);

    ImGui::Text("x");
    ImGui::SameLine();
    ImGui::DragFloat(fmt::format("{}_x", id).c_str(), &v3.x, .1f);
    ImGui::SameLine();

    ImGui::Text("y");
    ImGui::SameLine();
    ImGui::DragFloat(fmt::format("{}_y", id).c_str(), &v3.y, .1f);
    ImGui::SameLine();

    ImGui::Text("z");
    ImGui::SameLine();
    ImGui::DragFloat(fmt::format("{}_z", id).c_str(), &v3.z, .1f);

    ImGui::PopItemWidth();
}


template <>
void RenderProperty(
    std::shared_ptr<Noctis::ColorProperty> prop, 
    std::shared_ptr<Noctis::IPropertyHolder> propHolder)
{
    InlinedLabel(prop->GetName().c_str());

    Noctis::Color &c = prop->GetValue();
    std::string id = GenImGuiID("color_input", prop, propHolder);
    NoctisEditor::ColorEditEx(id.c_str(), c, ImGuiColorEditFlags_NoInputs);
}


template <>
void RenderProperty(
    std::shared_ptr<Noctis::StringProperty> prop, 
    std::shared_ptr<Noctis::IPropertyHolder> propHolder)
{
    NoctisEditor::InlinedLabel(prop->GetName().c_str());

    std::string &s = prop->GetValue();
    NoctisEditor::ResizableInputText(
        GenImGuiID("string_input", prop, propHolder).c_str(), 
        s, 
        false
    );
}


template <>
void RenderProperty(
    std::shared_ptr<Noctis::AssetProperty> prop, 
    std::shared_ptr<Noctis::IPropertyHolder> propHolder)
{
    NoctisEditor::InlinedLabel(prop->GetName().c_str());
        
    std::shared_ptr<Noctis::IAssetBase> &m = prop->GetValue();

    ImGui::Text(m->Name.c_str());
}

void RenderProperties(std::shared_ptr<Noctis::IPropertyHolder> propHolder)
{
    for (std::shared_ptr<Noctis::IPropertyBase> prop : propHolder->GetProperties())
    {
             if (auto c = std::dynamic_pointer_cast<Noctis::IntProperty>(prop))    RenderProperty(c, propHolder);
        else if (auto c = std::dynamic_pointer_cast<Noctis::FloatProperty>(prop))  RenderProperty(c, propHolder);
        else if (auto c = std::dynamic_pointer_cast<Noctis::Vec3Property>(prop))   RenderProperty(c, propHolder);
        else if (auto c = std::dynamic_pointer_cast<Noctis::ColorProperty>(prop))  RenderProperty(c, propHolder);
        else if (auto c = std::dynamic_pointer_cast<Noctis::StringProperty>(prop)) RenderProperty(c, propHolder);
        else if (auto c = std::dynamic_pointer_cast<Noctis::AssetProperty>(prop))  RenderProperty(c, propHolder);
    }
}


std::string GenImGuiID(
    std::string prefix, 
    std::shared_ptr<Noctis::IPropertyBase> property, 
    std::shared_ptr<Noctis::IPropertyHolder> propHolder
)
{
    return fmt::format(
        "##{}_{}_{}",
        prefix,
        propHolder->GetName(),
        property->GetName()
    );;
}

}
