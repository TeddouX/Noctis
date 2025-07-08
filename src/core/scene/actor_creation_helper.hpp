#pragma once
#include <regex>

#include "scene_manager.hpp"

#include "../project.hpp"


class ActorCreationHelper
{
public:
    ActorCreationHelper() = delete;

    static void CreateEmpty(Transform *parent);
    static void CreateSimpleShape(EmbeddedModel model, Transform *parent);
};