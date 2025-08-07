#pragma once
#include <xhash>
#include <stdint.h>

#include "component_manager.hpp"

#define MAX_ENTITIES UINT16_MAX


// Basically an ID
class Entity
{    
public:
    Entity() : m_id(0) {};
    Entity(ComponentManager *cm) : m_id(nextEntityID++), m_cm(cm) {};
    
    inline static void ResetCount() { nextEntityID = 1; }
    
    size_t GetID() const { return m_id; }
    bool   IsValid() { return m_id > 0; }
    
    bool operator==(const Entity& other) const { return m_id == other.m_id; }
    bool operator!=(const Entity& other) const { return m_id != other.m_id; }

    template <typename T>
    void AddComponent(const T &comp) { m_cm->AddComponent<T>(*this, comp); }

    template <typename T>
    T *GetComponent() const { return m_cm->GetComponent<T>(*this); }

    std::vector<std::shared_ptr<IComponent>> GetAllComponents() { return m_cm->GetAllComponents(*this); }

    operator size_t() const { return m_id; }    
    
private:
    // Keeping 0 for an invalid entity
    inline static size_t nextEntityID = 1;
    
    size_t m_id;
    ComponentManager *m_cm = nullptr;
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
