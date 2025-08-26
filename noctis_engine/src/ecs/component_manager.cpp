#include "ecs/component_manager.hpp"

namespace Noctis
{

std::vector<std::shared_ptr<IComponent>> ComponentManager::GetAllComponents(const Entity &entity)
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

}
