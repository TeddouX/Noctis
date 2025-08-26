#include <engine/ecs/component/component.hpp>
#include <engine/ecs/component/property/property.hpp>

namespace NoctisEditor
{

std::string GenImGuiID(
    std::string prefix, 
    std::shared_ptr<Noctis::IPropertyBase> property, 
    std::shared_ptr<Noctis::IComponent> component
);

template <typename T>
void RenderProperty(std::shared_ptr<T> prop, std::shared_ptr<Noctis::IComponent> comp);


void RenderComponentProperties(std::shared_ptr<Noctis::IComponent> comp);

}
