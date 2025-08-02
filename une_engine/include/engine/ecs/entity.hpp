#pragma once
#include <xhash>
#include <stdint.h>

#define MAX_ENTITIES UINT16_MAX



// Basically an ID
class Entity
{
    size_t m_id;

public:
    Entity() : m_id(0) {};
    Entity(size_t id) : m_id(id) {};

    inline static Entity Create() { return Entity(nextEntityID++); }
    inline static void ResetCount() { nextEntityID = 1; }
    
    size_t      GetID() const { return m_id; }
    inline bool IsValid() { return this->m_id > 0; }

    bool operator==(const Entity& other) const { return m_id == other.m_id; }
    bool operator!=(const Entity& other) const { return m_id != other.m_id; }

    operator size_t() const { return m_id; }    

private:
    // Keeping 0 for an invalid entity
    inline static size_t nextEntityID = 1;
};


namespace std 
{
    template<>
    struct hash<Entity> 
    {
        inline size_t operator()(const Entity& entity) const noexcept 
        {
            return std::hash<size_t>()(entity.GetID());
        }
    };
}
