#pragma once
#include <engine/ecs/component/transform_component.hpp>


class ActorCreationHelper
{
public:
    ActorCreationHelper() = delete;

    static void CreateEmpty(Transform *parent);
    static void CreateSimpleShape(std::string_view modelName, Transform *parent);
    static void CreateDirectionalLight(Transform *parent);

private:
    static void AddDefaultComponents(Entity entity, Transform *parent, const std::string &name);
};