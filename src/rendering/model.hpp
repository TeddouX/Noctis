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
#include "../core/logger.hpp"
#include "../core/filesystem.hpp"


class Model
{
public:
    Model() = default;
    Model(const fs::path &path);

    std::string GetBeautifiedName() const;
    inline const std::string &GetName() const { return this->m_name; }
    inline const fs::path     GetPath() const { return fs::absolute(this->m_path); }

    void Render(Shader &Shader) const;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Model, m_name)

private:
    std::vector<Mesh> m_meshes;
    std::string m_name;
    fs::path    m_path;

    std::vector<Mesh>    ProcessNode(aiNode *node, const aiScene *scene);
    Mesh                 ProcessMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> LoadTexturesFromMaterial(aiMaterial *material, aiTextureType type, TextureType texType);
};
