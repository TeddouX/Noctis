#pragma once
#include <stdint.h>

#define MAX_ENTITIES UINT16_MAX


static uint32_t nextEntityId;


// Basically an ID
class Entity
{
    uint32_t id;

public:
    static Entity Create() { return Entity(nextEntityId++); }
    
    uint32_t GetID() const { return id; }

    bool operator==(const Entity& other) const { return id == other.id; }
    bool operator!=(const Entity& other) const { return id != other.id; }

    operator uint32_t() const { return id; }    

private:
    explicit Entity(uint32_t id = 0) : id(id) {}
};


namespace std {
    template<>
    struct hash<Entity> {
        size_t operator()(const Entity& entity) const noexcept {
            return std::hash<uint32_t>()(entity.GetID());
        }
    };
}
