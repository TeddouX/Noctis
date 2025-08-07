#include "ecs/system/scripting_system.hpp"


void ScriptingSystem::CompileAll(ComponentManager &cm)
{
    auto &allScripts = cm.GetEntitiesWith<ScriptComponent>();
    ScriptBuilder sb;
    sb.Prepare();

    for (auto &[entity, script] : allScripts)
        sb.Build(script);
}


void ScriptingSystem::Start(ComponentManager &cm)
{
    auto &allScripts = cm.GetEntitiesWith<ScriptComponent>();
    
    for (auto &[entity, script] : allScripts)
        script.ExecuteStart();
}


void ScriptingSystem::Update(ComponentManager &cm, float dt)
{
    auto &allScripts = cm.GetEntitiesWith<ScriptComponent>();
    
    for (auto &[entity, script] : allScripts)
        script.ExecuteUpdate(dt);
}
