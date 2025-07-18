#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "../rendering/shader.hpp"
#include "../rendering/model.hpp"


inline constexpr std::string_view CUBE_MODEL_NAME = "Cube";
inline constexpr std::string_view CYLINDER_MODEL_NAME = "Cylinder";
inline constexpr std::string_view MONKEY_MODEL_NAME = "Monkey";
inline constexpr std::string_view SPHERE_MODEL_NAME = "Sphere";

inline constexpr std::string_view DEFAULT_SHADER_NAME = "Default";
inline constexpr std::string_view LIT_SHADER_NAME = "Lit";


class AssetManager
{
public:
    static AssetManager &GetInstance();

    void LoadEmbedded();

    void AddModel(const std::string &modelPath);
    void AddModel(const std::string &name, const std::string &modelPath);

    void AddShader(const std::string &name, const std::string &vrPath, const std::string &frPath);

    inline void AddTexture(const std::string &name, std::shared_ptr<ITexture> texture)
    {
        this->m_allTextures.emplace(name, texture);
    };

    inline std::shared_ptr<Model> GetModel(const std::string &name) { return this->m_allModels.at(name); }
    inline std::shared_ptr<Shader> GetShader(const std::string &name) { return this->m_allShaders.at(name); }
    inline std::shared_ptr<ITexture> GetTexture(const std::string &name) { return this->m_allTextures.at(name); }

private:
    // Might want to change how this works lol
    std::unordered_map<std::string, std::shared_ptr<ITexture>> m_allTextures;
    std::unordered_map<std::string, std::shared_ptr<Shader>>   m_allShaders;
    std::unordered_map<std::string, std::shared_ptr<Model>>    m_allModels;
    
    AssetManager() = default;

    void InitializeEmbeddedModels();
    void InitializeEmbeddedShaders();

    void AddAllTexturesFromModel(std::shared_ptr<Model> model);
};
