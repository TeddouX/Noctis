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
    Model(const fs::path &path, const std::string &name = "");

    std::string GetBeautifiedName() const;
    const std::string &GetName() const { return this->m_name; }
    const fs::path     GetPath() const { return fs::absolute(this->m_path); }

    const std::vector<std::shared_ptr<ITexture>> &GetTextures() const { return this->m_textures; }
    void ClearTextures() { this->m_textures.clear(); }

    void Render(Shader &shader, const Mat4 &modelMatrix) const;

private:
    std::vector<Mesh> m_meshes;
    // Used at loading to not have to remake every texture
    std::unordered_map<std::string, std::shared_ptr<BasicTexture>> m_textureCache;
    std::vector<std::shared_ptr<ITexture>> m_textures;
    std::string m_name;
    fs::path    m_path;

    std::array<aiTextureType, 5> m_supportedTextureTypes = {
        aiTextureType_DIFFUSE,
        aiTextureType_SPECULAR,
        aiTextureType_NORMALS,
        aiTextureType_HEIGHT
    };

    std::vector<Mesh> ProcessNode(aiNode *node, const aiScene *scene, Mat4 parentTransform);
    
    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);

    void LoadAllTextures(aiMaterial *material, const aiScene *scene);

    std::shared_ptr<BasicTexture> LoadTexture(aiMaterial *material, const aiScene *scene, aiTextureType aiTexType);
    
    // Helper functions
    bool IsSimpleTexture(aiMaterial *material);
};
