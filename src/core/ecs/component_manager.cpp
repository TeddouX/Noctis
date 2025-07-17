#include "component_manager.hpp"


const std::vector<std::shared_ptr<IComponent>> ComponentManager::GetAllComponents(Entity entity) const
{
    std::vector<std::shared_ptr<IComponent>> allComponents;

    for (auto &[typeIndex, componentArray] : this->m_componentArrays)
    {
        if (!componentArray->Has(entity))
            continue;

        allComponents.push_back(componentArray->GetUntyped(entity));
    }

    return allComponents;
}


void ComponentManager::Clear()
{
    for (auto &[type, compArray] : this->m_componentArrays)
        compArray->Clear();
}
