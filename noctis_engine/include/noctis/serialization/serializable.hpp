#include <nlohmann/json.hpp>

#include "../engine.hpp"

namespace Noctis
{

class NOCTIS_API ISerializable
{
public:
    virtual nlohmann::json Serialize() = 0;
    virtual void Deserialize(const nlohmann::json &j) = 0;
};

void to_json(nlohmann::json &j, const std::shared_ptr<ISerializable> &ptr);
void from_json(const nlohmann::json &j, std::shared_ptr<ISerializable> &ptr);

}

