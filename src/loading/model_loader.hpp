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


class ModelLoader
{
public:
    static std::shared_ptr<Model> LoadModel(const std::string &path);

private:
    static std::vector<Mesh> ProcessNode(aiNode *node, const aiScene *scene);
    static Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
    static std::vector<Texture> LoadTexturesFromMaterial(aiMaterial *material, aiTextureType type, TextureType texType);
};
