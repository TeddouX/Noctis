#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "asset.hpp"
#include "../engine.hpp"
#include "../rendering/shader.hpp"
#include "../rendering/model.hpp"


#define CUBE_MODEL_NAME "Cube"
#define CYLINDER_MODEL_NAME "Cylinder"
#define MONKEY_MODEL_NAME "Monkey"
#define SPHERE_MODEL_NAME "Sphere"

#define DEFAULT_SHADER_NAME "Default"
#define LIT_SHADER_NAME "Lit"


class NOCTIS_API IAssetManager
{
public:
    virtual ~IAssetManager() = default;
    virtual void InitEmbedded() = 0;
    // virtual void AddAsset(const std::string &name, AssetType type, std::shared_ptr<IAssetBase> asset) = 0;
    virtual std::shared_ptr<IAssetBase> GetAsset(AssetType type, const std::string &name) = 0;
};


class NOCTIS_API AssetManagerAccessor
{
public:
    static void SetAssetManager(std::shared_ptr<IAssetManager> assetManager) { s_assetManager = assetManager; }
    static std::shared_ptr<IAssetManager> GetAssetManager();

private:
    static inline std::shared_ptr<IAssetManager> s_assetManager;
};


class NOCTIS_API AssetManager
{
public:
    static AssetManager &GetInstance();

    void LoadEmbedded();

    void AddModel(Model &model);
    void AddShader(Shader &shader);

    inline void AddTexture(const std::string &name, std::shared_ptr<ITexture> texture)
    {
        this->m_allTextures.emplace(name, texture);
    };

    std::shared_ptr<Model> GetModel(const std::string &name);
    std::shared_ptr<Shader> GetShader(const std::string &name);
    std::shared_ptr<ITexture> GetTexture(const std::string &name);

private:
    // Might want to change how this works lol
    std::unordered_map<std::string, std::shared_ptr<ITexture>> m_allTextures;
    std::unordered_map<std::string, Shader>   m_allShaders;
    std::unordered_map<std::string, Model>    m_allModels;
    
    AssetManager() = default;

    void InitializeEmbeddedModels();
    void InitializeEmbeddedShaders();

    void AddAllTexturesFromModel(Model &model);
};
