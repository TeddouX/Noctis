#include "component.hpp"
#include "../../filesystem.hpp"


class ScriptComponent : public IComponent, public ISerializable
{
public:
    ScriptComponent() = default;

    ScriptComponent(const fs::path &scriptPath);

    void Serialize(json &j) const override;
    void Deserialize(const json &j) override;

private:
    fs::path m_scriptPath;
    std::vector<std::shared_ptr<IPropertyBase>> m_scriptProperties;
};