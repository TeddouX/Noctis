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
    const type_info &valueTy = property->GetValue(component).type();

    if (valueTy == typeid(std::reference_wrapper<int>))              // int 
        1;
    else if (valueTy == typeid(std::reference_wrapper<float>))       // float
        1;
    else if (valueTy == typeid(std::reference_wrapper<std::string>)) // string
        1;
    else if (valueTy == typeid(std::reference_wrapper<glm::vec3>))   // vector 3
        1;
}   
