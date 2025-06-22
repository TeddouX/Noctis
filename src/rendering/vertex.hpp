#pragma once
#include <glm/glm.hpp>


struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;

    Vertex() {}
    Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords)
        : position(position), normal(normal), texCoords(texCoords) {}
};
