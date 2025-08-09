
#include <engine/ecs/component/component.hpp>
#include <engine/ecs/component/property/property.hpp>



std::string GenImGuiID(
    std::string prefix, 
    std::shared_ptr<IPropertyBase> property, 
    IComponent *component
);

template <typename T>
void RenderProperty(std::shared_ptr<T> prop, IComponent *comp);


void RenderComponentProperties(IComponent *comp);
