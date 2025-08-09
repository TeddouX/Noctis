#include "ecs/component/script_component.hpp"


static void ExecuteFunction(asIScriptContext *ctx)
{
    int res = ctx->Execute();

	if(res != asEXECUTION_FINISHED && res == asEXECUTION_EXCEPTION)
	{
        LOG_ERR(
            "{} ({}): {}", 
            ctx->GetExceptionFunction()->GetDeclaration(), 
            ctx->GetExceptionLineNumber(), 
            ctx->GetExceptionString()
        );
	}
}


void ScriptComponent::ExecuteStart()
{
    if (!m_ctx)
        m_ctx = this->m_actorClass->GetEngine()->CreateContext();
    
    asIScriptFunction *startFunc = this->m_actorClass->GetMethodByName("Start");

    if (!startFunc)
        return;

    m_ctx->Prepare(startFunc);

    ExecuteFunction(m_ctx);
}


void ScriptComponent::ExecuteUpdate(float deltaTime)
{
    asIScriptFunction *updateFunc = this->m_actorClass->GetMethodByName("Update");

    if (!updateFunc)
        return;

    m_ctx->Prepare(updateFunc);
    // deltaTime should always be the first argument
    m_ctx->SetArgFloat(0, deltaTime);

    ExecuteFunction(m_ctx);
}


void ScriptComponent::End()
{
    m_ctx->Release();
    m_ctx = nullptr;
}


void ScriptComponent::Serialize(json &j) const
{
    START_SERIALIZATION(j)
        PROP_TO_JSON(m_scriptPath)
    END_SERIALIZATION()
}


void ScriptComponent::Deserialize(const json &j)
{
    PROP_FROM_JSON(j, m_scriptPath)
}
