#include "component_registry.hpp"

namespace Noctis
{

template <typename T>
bool ComponentRegistry::RegisterComponent(const std::string &name)
{
    static_assert(std::is_base_of<IComponent, T>::value, "Component must inherit from IComponent to be registered");

    ComponentRegEntry entry (
        [](Entity e, std::shared_ptr<IComponent> comp) -> bool
        {
            if (e.HasComponent<T>())
                return false;

            e.AddComponent(std::dynamic_pointer_cast<T>(comp));
            return true;
        },
        [](Entity e)
        {
            e.RemoveComponent<T>();
        },
        []()
        {
            return std::static_pointer_cast<IComponent>(
                std::make_shared<T>()
            );
        }
    );

    this->m_componentReg[name] = entry;

    return true;
}

}
