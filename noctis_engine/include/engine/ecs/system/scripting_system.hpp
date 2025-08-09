#include "system.hpp"
#include "../component/script_component.hpp"
#include "../../scripting/script_builder.hpp"


class NOCTIS_API ScriptingSystem : public ISystem
{
public:
    void CompileAll(ComponentManager &cm);

    void Start(ComponentManager &cm) override;
    void Update(ComponentManager &cm, float dt) override;
};