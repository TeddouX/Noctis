#pragma once
#include <noctis/ecs/component/transform_component.hpp>

namespace NoctisEditor
{

class ActorCreationHelper
{
public:
    ActorCreationHelper() = delete;

    static void CreateEmpty(Noctis::Transform *parent);
    static void CreateSimpleShape(
        std::string_view modelName, 
        Noctis::Transform *parent
    );
    static void CreateDirectionalLight(Noctis::Transform *parent);

private:
    static void AddDefaultComponents(
        Noctis::Entity entity, 
        Noctis::Transform *parent, 
        const std::string &name
    );
};

}
