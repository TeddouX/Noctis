#pragma once
#include <vector>
#include <regex>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../rendering/mesh.hpp"
#include "../rendering/vertex.hpp"
#include "../rendering/texture.hpp"
#include "../rendering/model.hpp"
#include "../logger.hpp"
#include "../filesystem.hpp"


class NOCTIS_API Model
{
public:
    Model(std::vector<Mesh> meshes)
        : m_meshes(meshes) {};

    const std::vector<Texture> &GetTextures() const { return this->m_textures; }

    void Render(Shader &shader, const Mat4 &modelMatrix) const;

private:
    std::vector<Mesh> m_meshes;
    std::vector<Texture> m_textures;
};
