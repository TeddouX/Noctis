#include "scripting/script_builder.hpp"


void ScriptBuilder::Prepare()
{
    int res;
    this->m_engine = asCreateScriptEngine();

	// Set the message callback to log errors
	res = this->m_engine->SetMessageCallback(asFUNCTION(MessageCallback), nullptr, asCALL_THISCALL);
    
    // Register string type
    RegisterStdString(m_engine);

    // RegisterAllEngineBindings(m_engine)
}


void ScriptBuilder::Build(ScriptComponent &scriptComp)
{
    const char *scriptPath = scriptComp.GetScriptPath().string().c_str();
    int res;

    CScriptBuilder builder;
    res = builder.StartNewModule(this->m_engine, scriptPath);
    res = builder.AddSectionFromFile(scriptPath);
    res = builder.BuildModule();

    if(res < 0)
    {
        LOG_ERR("Please correct the errors in the script and try again.\n");
        return;
    }

    asIScriptModule *mod = this->m_engine->GetModule(scriptPath, asGM_ONLY_IF_EXISTS);

	asITypeInfo *actorClass = this->m_engine->GetTypeInfoByDecl("IActor");
    asITypeInfo *type = nullptr;

	int typeCount = mod->GetObjectTypeCount();
	for(int i = 0; i < typeCount; i++)
	{
		type = mod->GetObjectTypeByIndex(i);

		if (type->DerivesFrom(actorClass))
			break;

		type = nullptr;
	}

	if (!type)
	{
		LOG_ERR(
			"Script {} doesn't contain any classes that inherit from IActor", 
			scriptComp.GetScriptPath().filename().string()
		)
		return;
	}

	scriptComp.SetActorClassInfo(type);
}


void ScriptBuilder::MessageCallback(const asSMessageInfo *msg)
{
	std::string formattedMsg = fmt::format(
		"{} ({}, {}): {}", 
		msg->section, 
		msg->row, msg->col, 
		msg->message
	);

	if (msg->type == asMSGTYPE_INFORMATION)
		LOG_INFO(formattedMsg)
	else if (msg->type == asMSGTYPE_WARNING)
		LOG_WARN(formattedMsg)
	else if (msg->type == asMSGTYPE_ERROR)
		LOG_ERR(formattedMsg)
}

