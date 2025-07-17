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

    inline std::shared_ptr<Model> GetModel(const std::string &name) { return this->m_allModels.at(name); }
    inline std::shared_ptr<Shader> GetShader(const std::string &name) { return this->m_allShaders.at(name); }

private:
    std::unordered_map<std::string, std::shared_ptr<Model>> m_allModels;
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_allShaders;
    
    AssetManager() = default;

    void InitializeEmbeddedModels();
    void InitializeEmbeddedShaders();
};
