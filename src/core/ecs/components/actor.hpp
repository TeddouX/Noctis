#pragma once
#include <memory>
#include <vector>
#include <string>

#include "../entity.hpp"


class Actor
{
public:
    std::string name;

    Actor(const std::string &name, std::shared_ptr<Actor> parent = nullptr);
    
    inline bool IsChild() const { return this->m_parent != nullptr; } 
    inline bool HasChildren() const { return !this->m_children.empty(); } 
    inline void AddChild(Actor *child) { this->m_children.push_back(child); } 
    inline const std::vector<Actor*> &GetChildren() const { return this->m_children; } 

private:
    std::shared_ptr<Actor> m_parent;

    std::vector<Actor*> m_children;
};