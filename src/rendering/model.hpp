#pragma once
#include <vector>

#include "mesh.hpp"
#include "shader.hpp"


class Model
{
public:
    Model(std::vector<Mesh> &meshes);

    void Render(Shader &Shader);

private:
    std::vector<Mesh> m_meshes;
};
