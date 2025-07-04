#pragma once
#include <memory>
#include <vector>
#include <string>

#include "../entity.hpp"


class Actor
{
public:
    Actor(const std::string &name);

    // Returns a reference to this actor's name
    inline std::string &GetName() { return this->m_name; }

private:
    std::string m_name;
};