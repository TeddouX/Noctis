#pragma once
#include <memory>

#define MAX_ENTITIES UINT16_MAX


class Entity
{
public:
    std::uint32_t getId() const { return id; }

    bool operator==(const Entity& other) const { return id == other.id; }
    bool operator!=(const Entity& other) const { return id != other.id; }

    operator std::uint32_t() const { return id; }

    static Entity create() { return Entity(nextId++); }

private:
    explicit Entity(std::uint32_t id = 0) : id(id) {}

    std::uint32_t id;

    static std::uint32_t nextId;
};
