#pragma once
#include <xhash>
#include <stdint.h>

#include "component_manager.hpp"
#include "../engine.hpp"

#define MAX_ENTITIES UINT16_MAX

namespace Noctis
{

// Basically an ID
class NOCTIS_API Entity
{    
public:
    Entity() : m_id(0) {};
    Entity(ComponentManager *cm) : m_id(nextEntityID++), m_cm(cm) {};
    
    inline static void ResetCount() { nextEntityID = 1; }
    
    uint64_t GetID() const { return m_id; }
    bool     IsValid() { return m_id != 0; }
    
    bool operator==(const Entity& other) const { return m_id == other.m_id; }
    bool operator!=(const Entity& other) const { return m_id != other.m_id; }

    template <typename T>
    void AddComponent(std::shared_ptr<T> comp) { m_cm->AddComponent<T>(*this, comp); }

    template <typename T>
    void RemoveComponent() { return m_cm->RemoveComponent<T>(*this); }

    template <typename T>
    std::shared_ptr<T> GetComponent() const { return m_cm->GetComponent<T>(*this); }

    template <typename T>
    bool HasComponent() const { return m_cm->HasComponent<T>(*this); }

    std::vector<std::shared_ptr<IComponent>> GetAllComponents() { return m_cm->GetAllComponents(*this); }

    operator size_t() const { return m_id; }    
    
private:
    // Keeping 0 for an invalid entity
    inline static uint64_t nextEntityID = 1;
    
    uint64_t m_id;
    ComponentManager *m_cm = nullptr;
};

}


namespace std 
{
    template<>
    struct hash<Noctis::Entity> 
    {
        inline size_t operator()(const Noctis::Entity& entity) const noexcept 
        {
            return std::hash<uint64_t>()(entity.GetID());
        }
    };
}
