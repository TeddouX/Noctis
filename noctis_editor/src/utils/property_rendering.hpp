
#include <engine/ecs/component/component.hpp>
#include <engine/ecs/component/property/property.hpp>



std::string GenImGuiID(
    std::string prefix, 
    std::shared_ptr<IPropertyBase> property, 
    std::shared_ptr<IComponent> component
);

template <typename T>
void RenderProperty(std::shared_ptr<T> prop, std::shared_ptr<IComponent> comp);


void RenderComponentProperties(std::shared_ptr<IComponent> comp);
