#pragma once
#include <stdint.h>

#define MAX_ENTITIES UINT16_MAX


// Keeping 0 for an invalid entity
static size_t nextEntityId = 1;

// Basically an ID
class Entity
{
    size_t m_id;

public:
    Entity() : m_id(0) {};
    Entity(size_t id) : m_id(id) {};

    static Entity Create() { return Entity(nextEntityId++); }
    
    size_t      GetID() const { return m_id; }
    inline bool IsValid() { return this->m_id > 0; }

    bool operator==(const Entity& other) const { return m_id == other.m_id; }
    bool operator!=(const Entity& other) const { return m_id != other.m_id; }

    operator size_t() const { return m_id; }    
};


namespace std {
    template<>
    struct hash<Entity> {
        size_t operator()(const Entity& entity) const noexcept {
            return std::hash<size_t>()(entity.GetID());
        }
    };
}
