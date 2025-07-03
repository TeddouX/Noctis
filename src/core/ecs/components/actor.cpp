#include "actor.hpp"


Actor::Actor(const std::string &name, std::shared_ptr<Actor> parent)
    : name(name), m_parent(parent)
{
    // Add this actor to the list of children of its parent
    if (parent)
        parent->AddChild(this);
}
