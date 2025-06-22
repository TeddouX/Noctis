#include "model.hpp"


Model::Model(std::vector<Mesh> &meshes)
    : m_meshes(meshes) 
{
}


void Model::Render(Shader &shader)
{
    for (Mesh mesh : this->m_meshes)
        mesh.Render(shader);
}
