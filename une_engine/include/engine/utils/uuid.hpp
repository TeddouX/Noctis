#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <array>
#include <random>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <functional>

#include "../logger.hpp"


using json = nlohmann::json;


class UNE_API UUIDv4
{
public:
    UUIDv4() = default;

    static UUIDv4 Generate();
    static UUIDv4 FromString(const std::string &hex);
    
    bool operator==(const UUIDv4& other) const
    {
        return this->m_bytes == other.m_bytes;
    }

    std::string ToString() const;

    std::array<uint8_t, 16> GetBytes() const { return this->m_bytes; }

private:
    UUIDv4(const std::array<uint8_t, 16> &bytes)
        : m_bytes(bytes) {}

    std::array<uint8_t, 16> m_bytes;
};


void from_json(const json &j, UUIDv4 &uuid);
void to_json(json &j, const UUIDv4 &uuid);


namespace std 
{
    template<>
    struct hash<UUIDv4> 
    {
        size_t operator()(const UUIDv4& uuid) const noexcept 
        {
            // Fowler–Noll–Vo hash function from wikipedia:
            // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function

            size_t hash = _FNV_offset_basis;

            for (uint8_t byte : uuid.GetBytes())
            {
                hash ^= byte;
                hash *= _FNV_prime;
            }

            return hash;
        }
    };
}
