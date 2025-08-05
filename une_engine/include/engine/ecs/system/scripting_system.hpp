#include "system.hpp"


class ScriptingSystem : public ISystem
{
    void Update(const ComponentManager &cm, float dt) override;
};