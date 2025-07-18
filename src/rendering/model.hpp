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
    /// @brief This constructor should only be used by the asset manager
    /// If a new model needs to be added, add it through the asset manager
    Model(const fs::path &path, const std::string &name = "");

    std::string GetBeautifiedName() const;
    inline const std::string &GetName() const { return this->m_name; }
    inline const fs::path     GetPath() const { return fs::absolute(this->m_path); }

    inline const std::unordered_map<std::string, std::shared_ptr<BasicTexture>> &GetTextureCache() const 
    {
        return this->m_textureCache;
    };

    inline void ClearTextureCache() { this->m_textureCache.clear(); }

    void Render(Shader &Shader) const;

private:
    std::vector<Mesh> m_meshes;
    // Used at loading to not have to remake every texture
    std::unordered_map<std::string, std::shared_ptr<BasicTexture>> m_textureCache;
    std::string m_name;
    fs::path    m_path;

    std::array<aiTextureType, 5> m_supportedTextureTypes = {
        aiTextureType_DIFFUSE,
        aiTextureType_SPECULAR,
        aiTextureType_NORMALS,
        aiTextureType_METALNESS,
        aiTextureType_HEIGHT
    };

    std::shared_ptr<ITexture> LoadAllTextures(aiMaterial *material, const aiScene *scene);
    std::shared_ptr<BasicTexture> LoadTexture(aiMaterial *material, const aiScene *scene, aiTextureType aiTexType);
    std::vector<Mesh> ProcessNode(aiNode *node, const aiScene *scene);
    Mesh              ProcessMesh(aiMesh *mesh, const aiScene *scene);
    
    // Helper functions
    bool        IsSimpleTexture(aiMaterial *material);
    TextureType TexTypeFromAssimp(aiTextureType assimp);
};
