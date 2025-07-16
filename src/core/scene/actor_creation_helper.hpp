#pragma once
#include <regex>

#include "scene_manager.hpp"
#include "../project.hpp"
#include "../ecs/component/all_components.hpp"


class ActorCreationHelper
{
public:
    ActorCreationHelper() = delete;

    static void CreateEmpty(Transform *parent);
    static void CreateSimpleShape(std::string_view modelName, Transform *parent);
    static void CreateDirectionalLight(Transform *parent);

private:
    static void AddDefaultComponents(ComponentManager &cm, Entity entity, Transform *parent, const std::string &name);
};