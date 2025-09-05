#include "serialization/serializable.hpp"
#include "logger.hpp"

namespace Noctis
{

void to_json(nlohmann::json &j, const std::shared_ptr<ISerializable> &ptr)
{
    if (ptr)
    {
        try 
        {
            j = ptr->Serialize();
        }
        catch (const std::exception &e)
        {
            LOG_ERR("Error while serizalizing: {}", e.what());
        }
    }
    else
        j = nullptr;
}

void from_json(const nlohmann::json &j, std::shared_ptr<ISerializable> &ptr)
{
    if (j.is_null())
    {
        ptr = nullptr;
        return;
    }

    try 
    {
        ptr->Deserialize(j);
    }
    catch (const std::exception &e)
    {
        LOG_ERR("Error while deserializing: {}", e.what());
    }
}

} // namespace Noctis
