#include "utils/uuid.hpp"


UUIDv4 UUIDv4::Generate()
{
    auto now = std::chrono::steady_clock::now().time_since_epoch().count();
    uint32_t seed = (uint32_t)now ^ (now >> 32);

    std::mt19937 rng(seed);

    std::array<uint8_t, 16> bytes;
    for (int i = 0; i < bytes.size(); i++)
    {
        bytes[i] = rng() % 256;
    }

    // Version (4)
    bytes[6] = (bytes[6] & 0x0F) | 0x40;
    // Variant
    bytes[8] = (bytes[8] & 0x3F) | 0x80;

    return UUIDv4(bytes);
}


UUIDv4 UUIDv4::FromString(const std::string &hex)
{
    std::string cleanHex;
    cleanHex.reserve(32);

    // Remove dashes or any non-hex characters
    for (char c : hex) 
    {
        if (std::isxdigit(static_cast<unsigned char>(c)))
            cleanHex += c;
    }

    if (cleanHex.length() != 32)
    {
        LOG_ERR("Hex string must have exactly 32 hex characters for conversion to a UUID. Got {} for string {}", 
            cleanHex.length(), 
            hex
        )

        return UUIDv4();
    }

    std::array<uint8_t, 16> bytes;
    for (size_t i = 0; i < bytes.size(); ++i) 
    {
        std::string byteStr = cleanHex.substr(i * 2, 2);
        bytes[i] = static_cast<uint8_t>(std::stoul(byteStr, nullptr, 16));
    }

    return UUIDv4(bytes);
}


std::string UUIDv4::ToString() const
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');

    for (size_t i = 0; i < this->m_bytes.size(); ++i) 
    {
        oss << std::setw(2) << static_cast<int>(this->m_bytes[i]);

        // Add dashes to the string
        if (i == 3 || i == 5 || i == 7 || i == 9) 
            oss << '-';
    }

    return oss.str();
}


void from_json(const json &j, UUIDv4 &uuid)
{
    uuid = UUIDv4::FromString(j.at("value").get<std::string>());
}


void to_json(json &j, const UUIDv4 &uuid)
{
    j = json{
        {"value", uuid.ToString()}     
    };
}
