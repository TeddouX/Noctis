#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "../rendering/shader.hpp"
#include "../rendering/model.hpp"


enum EmbeddedModel
{
    CUBE  
};

enum EmbeddedShader
{
    DEFAULT // Basically no logic
};


class AssetManager
{
public:
    AssetManager();

    void AddModel(const std::string &modelPath);
    inline std::shared_ptr<Model> GetModel(const std::string &name) { return this->m_allModels.at(name); }
    inline std::shared_ptr<Model> GetEmbeddedModel(EmbeddedModel model) { return this->m_embeddedModels.at(model); }

    inline std::shared_ptr<Shader> GetEmbeddedShader(EmbeddedShader shader) { return this->m_embeddedShaders.at(shader); }

private:
    // name -> model
    std::unordered_map<std::string, std::shared_ptr<Model>> m_allModels;
    std::unordered_map<EmbeddedModel, std::shared_ptr<Model>> m_embeddedModels;

    std::unordered_map<EmbeddedShader, std::shared_ptr<Shader>> m_embeddedShaders;

    void InitializeEmbeddedModels();
    void InitializeEmbeddedShaders();
};
