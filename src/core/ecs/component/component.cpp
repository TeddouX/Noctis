#include "component.hpp"


void to_json(json &j, const std::shared_ptr<ISerializable> &ptr)
{
    if (ptr)
        ptr->Serialize(j);
    else
        j = nullptr;
}

void from_json(const json &j, std::shared_ptr<ISerializable> &ptr)
{
    if (j.is_null())
    {
        ptr = nullptr;
        return;
    }

    std::string type = j.at("type");
    auto it = ::componentDeserializerReg.find(type);
    if (it == ::componentDeserializerReg.end())
    {
        LOG_ERR("Unknown type for deserialization: {}", type)
        ptr = nullptr;
        return;
    }

    ptr = it->second(j);
    ptr->Deserialize(j);
}
