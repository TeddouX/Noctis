#pragma once
#include "../core/math/math.hpp"


struct Vertex
{
    Vec3 position;
    Vec3 normal;
    Vec2 texCoords;

    Vertex() {}
    Vertex(Vec3 position, Vec3 normal, Vec2 texCoords)
        : position(position), normal(normal), texCoords(texCoords) {}
};
