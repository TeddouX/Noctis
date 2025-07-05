#pragma once
#include "actor.hpp"
#include "model_component.hpp"
#include "transform.hpp"
#include "material.hpp"


class TestComponent : public IComponent
{
public:
    ENABLE_REFLECTION(TestComponent)

    PROPERTY_D(int, a, 10)
    PROPERTY_D(float, b, 100)
    PROPERTY_D(std::string, c, "lorem ipsum")
    PROPERTY_D(glm::vec3, d, glm::vec3(0, 1, -10))
};
