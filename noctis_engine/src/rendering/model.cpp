#include "rendering/model.hpp"


void Model::Render(Shader &shader, const Mat4 &modelMatrix) const
{
    // Render every mesh from this model
    for (Mesh mesh : this->m_meshes)
        mesh.Render(shader, modelMatrix);
}

