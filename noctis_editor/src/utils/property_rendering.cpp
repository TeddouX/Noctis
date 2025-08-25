#include "property_rendering.hpp"

#include <imgui.h>
#include <engine/ecs/component/property/all_properties.hpp>

#include "imgui_utils.hpp"


std::string GenImGuiID(
    std::string prefix, 
    std::shared_ptr<IPropertyBase> property, 
    std::shared_ptr<IComponent> component
)
{
    return fmt::format(
        "##{}_{}_{}",
        prefix,
        component->GetName(),
        property->GetName()
    );;
}


template <>
void RenderProperty(std::shared_ptr<IntProperty> prop, std::shared_ptr<IComponent> comp)
{
    ImGui::InlinedLabel(prop->GetName().c_str());

    int &i = prop->GetValue();
    ImGui::DragInt(
        GenImGuiID("int_input", prop, comp).c_str(), 
        &i, 
        (float)prop->stepSize, 
        prop->minVal, prop->maxVal
    );
}


template <>
void RenderProperty(std::shared_ptr<FloatProperty> prop, std::shared_ptr<IComponent> comp)
{
    ImGui::InlinedLabel(prop->GetName().c_str());

    float &f = prop->GetValue();
    ImGui::DragFloat(GenImGuiID("int_input", prop, comp).c_str(), 
        &f, 
        prop->stepSize, 
        prop->minVal, prop->maxVal
    );
}


template <>
void RenderProperty(std::shared_ptr<Vec3Property> prop, std::shared_ptr<IComponent> comp)
{
    ImGui::InlinedLabel(prop->GetName().c_str());

    Vec3 &v3 = prop->GetValue();
    std::string id = GenImGuiID("vec3_input", prop, comp);

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
void RenderProperty(std::shared_ptr<ColorProperty> prop, std::shared_ptr<IComponent> comp)
{
    ImGui::InlinedLabel(prop->GetName().c_str());

    Color &c = prop->GetValue();
    std::string id = GenImGuiID("color_input", prop, comp);
    ImGui::ColorEditEx(id.c_str(), c, ImGuiColorEditFlags_NoInputs);
}


template <>
void RenderProperty(std::shared_ptr<StringProperty> prop, std::shared_ptr<IComponent> comp)
{
    ImGui::InlinedLabel(prop->GetName().c_str());

    std::string &s = prop->GetValue();
    ImGui::ResizableInputText(GenImGuiID("string_input", prop, comp).c_str(), s, true);
}


template <>
void RenderProperty(std::shared_ptr<AssetProperty> prop, std::shared_ptr<IComponent> comp)
{
    ImGui::InlinedLabel(prop->GetName().c_str());
        
    std::shared_ptr<IAssetBase> &m = prop->GetValue();

    ImGui::Text(m->Name.c_str());
}

void RenderComponentProperties(std::shared_ptr<IComponent> comp)
{
    for (std::shared_ptr<IPropertyBase> prop : comp->GetProperties())
    {
        if (auto c = std::dynamic_pointer_cast<IntProperty>(prop))
            RenderProperty(c, comp);
        else if (auto c = std::dynamic_pointer_cast<FloatProperty>(prop))
            RenderProperty(c, comp);
        else if (auto c = std::dynamic_pointer_cast<Vec3Property>(prop))
            RenderProperty(c, comp);
        else if (auto c = std::dynamic_pointer_cast<ColorProperty>(prop))
            RenderProperty(c, comp);
        else if (auto c = std::dynamic_pointer_cast<StringProperty>(prop))
            RenderProperty(c, comp);
        else if (auto c = std::dynamic_pointer_cast<AssetProperty>(prop))
            RenderProperty(c, comp);
    }
}
