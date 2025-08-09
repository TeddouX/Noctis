#include "property_rendering.hpp"

#include <imgui.h>
#include <engine/ecs/component/property/all_properties.hpp>

#include "imgui_utils.hpp"


std::string GenImGuiID(
    std::string prefix, 
    std::shared_ptr<IPropertyBase> property, 
    IComponent *component
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
void RenderProperty(std::shared_ptr<IntProperty> prop, IComponent *comp)
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
void RenderProperty(std::shared_ptr<FloatProperty> prop, IComponent *comp)
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
void RenderProperty(std::shared_ptr<Vec3Property> prop, IComponent *comp)
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

    ImGui::PopItemWidth();;
}


template <>
void RenderProperty(std::shared_ptr<ColorProperty> prop, IComponent *comp)
{
    ImGui::InlinedLabel(prop->GetName().c_str());

    Color &c = prop->GetValue();
    std::string id = GenImGuiID("color_input", prop, comp);
    ImGui::ColorEditEx(id.c_str(), c, ImGuiColorEditFlags_NoInputs);
}


template <>
void RenderProperty(std::shared_ptr<StringProperty> prop, IComponent *comp)
{
    ImGui::InlinedLabel(prop->GetName().c_str());

    std::string &s = prop->GetValue();
    ImGui::ResizableInputText(GenImGuiID("string_input", prop, comp).c_str(), s, true);
}


template <>
void RenderProperty(std::shared_ptr<ModelProperty> prop, IComponent *comp)
{
    ImGui::InlinedLabel(prop->GetName().c_str());
        
    Model &m = prop->GetValue();

    ImGui::Text(m.GetBeautifiedName().c_str());
}


template <>
void RenderProperty(std::shared_ptr<ShaderProperty> prop, IComponent *comp)
{
    ImGui::InlinedLabel(prop->GetName().c_str());
        
    Shader &m = prop->GetValue();

    ImGui::Text(m.GetName().c_str());
}

void RenderComponentProperties(IComponent *comp)
{
    std::string componentName = comp->GetName();

    bool open = ImGui::CollapsingHeader(componentName.c_str(), ImGuiTreeNodeFlags_DefaultOpen);

    if (!open)
        return;

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
        else if (auto c = std::dynamic_pointer_cast<ModelProperty>(prop))
            RenderProperty(c, comp);
        else if (auto c = std::dynamic_pointer_cast<ShaderProperty>(prop))
            RenderProperty(c, comp);
    }
}



