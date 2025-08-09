#pragma once
#include "../math/math.hpp"


struct NOCTIS_API Vertex
{
    Vec3 position;
    Vec3 normal;
    Vec2 texCoords;

    Vertex() 
        : position(0), normal(0), texCoords(0) {}

    Vertex(Vec3 position, Vec3 normal, Vec2 texCoords)
        : position(position), normal(normal), texCoords(texCoords) {}
};
