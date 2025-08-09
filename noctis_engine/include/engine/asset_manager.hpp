#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "engine.hpp"
#include "rendering/shader.hpp"
#include "rendering/model.hpp"


inline constexpr std::string_view CUBE_MODEL_NAME = "Cube";
inline constexpr std::string_view CYLINDER_MODEL_NAME = "Cylinder";
inline constexpr std::string_view MONKEY_MODEL_NAME = "Monkey";
inline constexpr std::string_view SPHERE_MODEL_NAME = "Sphere";

inline constexpr std::string_view DEFAULT_SHADER_NAME = "Default";
inline constexpr std::string_view LIT_SHADER_NAME = "Lit";


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
