#include <angelscript.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>

#include "../filesystem.hpp"
#include "../ecs/component/script_component.hpp"


class ScriptBuilder
{
public:
    ScriptBuilder() = default;

    void Prepare();
    void Build(std::shared_ptr<ScriptComponent> scriptComp);

    asIScriptEngine *GetScriptEngine() { return this->m_engine; }

private:
    asIScriptEngine *m_engine = nullptr;

    static void MessageCallback(const asSMessageInfo *msg);
};
