#pragma once
#include <memory>
// #include "../manager.hpp"

#define MAX_ENTITIES UINT16_MAX


static std::uint32_t nextEntityId;


class Entity
{
    std::uint32_t id;

public:
    static Entity Create() { return Entity(nextEntityId++); }

    std::uint32_t GetID() const { return id; }

    bool operator==(const Entity& other) const { return id == other.id; }
    bool operator!=(const Entity& other) const { return id != other.id; }

    operator std::uint32_t() const { return id; }    

private:
    explicit Entity(std::uint32_t id = 0) : id(id) {}
    
};


namespace std {
    template<>
    struct hash<Entity> {
        size_t operator()(const Entity& entity) const noexcept {
            return std::hash<uint32_t>()(entity.GetID());
        }
    };
}
