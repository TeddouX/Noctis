#pragma once
#include <angelscript.h>

#include "component.hpp"
#include "../../filesystem.hpp"


class NOCTIS_API ScriptComponent : public IComponent
{
public:
    REGISTER_COMPONENT(ScriptComponent, "Script")

    ScriptComponent() = default;
    ScriptComponent(const fs::path &scriptPath)
        : m_scriptPath(scriptPath) {}

    const fs::path &GetScriptPath() const { return this->m_scriptPath; }

    void SetActorClassInfo(asITypeInfo *actorClass) { this->m_actorClass = actorClass; }

    void ExecuteStart();
    void ExecuteUpdate(float deltaTime);
    void End();

    void Serialize(json &j) const override;
    void Deserialize(const json &j) override;

private:
    // Context is shared between scripts
    inline static asIScriptContext *m_ctx = nullptr;
    asITypeInfo *m_actorClass = nullptr;
    
    fs::path m_scriptPath;
    std::vector<std::shared_ptr<IPropertyBase>> m_scriptProperties;
};