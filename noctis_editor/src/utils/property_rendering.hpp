#include <noctis/ecs/component/component.hpp>
#include <noctis/property/property.hpp>

namespace NoctisEditor
{

template <typename T>
void RenderProperty(
    std::shared_ptr<T> prop, 
    std::shared_ptr<Noctis::IPropertyHolder> propHolder);
void RenderProperties(std::shared_ptr<Noctis::IPropertyHolder> propHolder);

}
