#include "actor_properties.hpp"


void ActorPropertiesWidget::Render()
{
    ImGui::Begin(std::string(ActorPropertiesWidget::name).c_str());

    Scene *currScene = SCENE_MANAGER().GetCurrScene();

    if (currScene && this->m_selectedEntity)
    {
        ComponentManager &cm = currScene->GetComponentManager();
        std::vector<std::shared_ptr<IComponent>> allComponents 
            = cm.GetAllComponents(*this->m_selectedEntity);
        
        for (std::shared_ptr<IComponent> &component : allComponents)
            if (ImGui::CollapsingHeader(component->_GetComponentName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
                for (IProperty *prop : component->_GetComponentProperties())
                    this->ProcessProperty(prop, component.get());  
    }

    ImGui::End();
}


void ActorPropertiesWidget::ProcessProperty(IProperty *property, IComponent *component)
{
    std::any value = property->GetValue(component);

    if (value.type() == typeid(std::reference_wrapper<int>))              // int 
    {
        ImGui::InlinedLabel(property->GetName().c_str());

        int &i = std::any_cast<std::reference_wrapper<int>>(value);
        ImGui::DragInt(GenImGuiID("int_input", property, component).c_str(), &i);
    }
    else if (value.type() == typeid(std::reference_wrapper<float>))       // float
    {
        ImGui::InlinedLabel(property->GetName().c_str());

        float &f = std::any_cast<std::reference_wrapper<float>>(value);
        ImGui::DragFloat(GenImGuiID("float_input", property, component).c_str(), &f, .1f);
    }
    else if (value.type() == typeid(std::reference_wrapper<std::string>)) // string
    {
        ImGui::InlinedLabel(property->GetName().c_str());

        std::string &s = std::any_cast<std::reference_wrapper<std::string>>(value);
        ImGui::ResizableInputText(GenImGuiID("string_input", property, component).c_str(), s);
    }
    else if (value.type() == typeid(std::reference_wrapper<glm::vec3>))   // vector 3
        1;
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
