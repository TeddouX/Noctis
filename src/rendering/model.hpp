#pragma once
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../rendering/mesh.hpp"
#include "../rendering/vertex.hpp"
#include "../rendering/texture.hpp"
#include "../rendering/model.hpp"
#include "../core/logger.hpp"


class Model
{
public:
    Model(const std::string &path);
    Model(const std::string &name, const std::string &objData);

    inline const std::string &GetName() { return this->m_name; }

    void Render(Shader &Shader) const;
private:
    std::string m_name;
    std::vector<Mesh> m_meshes;

    std::vector<Mesh>    ProcessNode(aiNode *node, const aiScene *scene);
    Mesh                 ProcessMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> LoadTexturesFromMaterial(aiMaterial *material, aiTextureType type, TextureType texType);
};
