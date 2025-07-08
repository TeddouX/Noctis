#include "actor_properties.hpp"


void ActorPropertiesWidget::Render()
{
    ImGui::Begin(std::string(ActorPropertiesWidget::name).c_str());

    Scene *currScene = SCENE_MANAGER().GetCurrScene();
    Entity selectedEntity = currScene->GetSelectedEntity();

    if (currScene && selectedEntity.IsValid())
    {
        ComponentManager &cm = currScene->GetComponentManager();
        std::vector<std::shared_ptr<IComponent>> allComponents = cm.GetAllComponents(selectedEntity);

        // The actor component is handled differently from the others
        // It shouldn't be rendered as a collapsing header
        HandleActor(cm.GetComponent<Actor>(selectedEntity).get());
        
        // Transform is processed individually here because it should be inserted at the top of everything
        IterateComponentProperties(cm.GetComponent<Transform>(selectedEntity));

        for (std::shared_ptr<IComponent> &component : allComponents)
        {
            // Actor and transform are already handled
            if (std::dynamic_pointer_cast<Actor>(component) || 
                std::dynamic_pointer_cast<Transform>(component))
                continue; 

            IterateComponentProperties(component);
        }  
    }

    ImGui::End();
}


void ActorPropertiesWidget::IterateComponentProperties(std::shared_ptr<IComponent> component)
{
    std::string componentName = component->_GetComponentName();
    std::string headerTitle = SplitStringAtCapital(componentName);

    if (ImGui::CollapsingHeader(headerTitle.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
        for (IProperty *prop : component->_GetComponentProperties())
            ProcessProperty(prop, component.get());
}


void ActorPropertiesWidget::HandleActor(IComponent *component)
{
    ImGui::SeparatorText("Actor");

    for (IProperty *prop : component->_GetComponentProperties())
    {
        std::any value = prop->GetValue(component);

        // The actor's name
        if (value.type() == typeid(std::reference_wrapper<std::string>)) 
        {
            std::string &actorName = std::any_cast<std::reference_wrapper<std::string>>(value);
            ImGui::ResizableInputText(GenImGuiID("string_input", prop, component).c_str(), actorName);
        }
    }

    ImGui::SeparatorText("Components");
}


void ActorPropertiesWidget::ProcessProperty(IProperty *property, IComponent *component)
{
    std::any value = property->GetValue(component);

    if (value.type() == typeid(std::reference_wrapper<int>))              // int 
    {
        ImGui::InlinedLabel(property->GetBeautifiedName().c_str());

        int &i = std::any_cast<std::reference_wrapper<int>>(value);
        ImGui::DragInt(GenImGuiID("int_input", property, component).c_str(), &i);
    }
    else if (value.type() == typeid(std::reference_wrapper<float>))       // float
    {
        ImGui::InlinedLabel(property->GetBeautifiedName().c_str());

        float &f = std::any_cast<std::reference_wrapper<float>>(value);
        ImGui::DragFloat(GenImGuiID("float_input", property, component).c_str(), &f, .1f);
    }
    else if (value.type() == typeid(std::reference_wrapper<std::string>)) // string
    {
        ImGui::InlinedLabel(property->GetBeautifiedName().c_str());

        std::string &s = std::any_cast<std::reference_wrapper<std::string>>(value);
        ImGui::ResizableInputText(GenImGuiID("string_input", property, component).c_str(), s);
    }
    else if (value.type() == typeid(std::reference_wrapper<Vec3>))        // vector 3
    {
        ImGui::InlinedLabel(property->GetBeautifiedName().c_str());

        Vec3 &v3 = std::any_cast<std::reference_wrapper<Vec3>>(value);
        std::string id = GenImGuiID("vec3_input", property, component);

        ImGui::PushItemWidth(100.f);

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
    else if (value.type() == typeid(std::reference_wrapper<Model>))       // Model (temporary)
    {
        ImGui::InlinedLabel(property->GetBeautifiedName().c_str());
        
        Model &m = std::any_cast<std::reference_wrapper<Model>>(value);
        ImGui::Text(m.GetBeautifiedName().c_str());
    }
    else if (value.type() == typeid(std::reference_wrapper<Color>))       // Color
    {
        ImGui::InlinedLabel(property->GetBeautifiedName().c_str());

        Color &c = std::any_cast<std::reference_wrapper<Color>>(value);
        std::string id = GenImGuiID("color_input", property, component);
        ImGui::ColorEditEx(id.c_str(), c, ImGuiColorEditFlags_NoInputs);
    }
}   


std::string ActorPropertiesWidget::GenImGuiID(std::string prefix, IProperty *property, IComponent *component)
{
    return fmt::format(
        "##{}_{}_{}",
        prefix,
        component->_GetComponentName(),
        property->GetName()
    );;
}
