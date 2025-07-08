#include "asset_manager.hpp"


AssetManager::AssetManager()
{
    this->InitializeEmbeddedModels();
    this->InitializeEmbeddedShaders();
}


void AssetManager::AddModel(const std::string &modelPath)
{
    std::shared_ptr<Model> model = std::make_shared<Model>(modelPath);

    this->m_allModels.emplace(model->GetName(), model);
}


void AssetManager::InitializeEmbeddedModels()
{
    this->m_embeddedModels.resize(EmbeddedModel::_EMBEDDED_MODELS_ALL);
    this->m_embeddedModels[EmbeddedModel::CUBE] = std::make_shared<Model>("./assets/models/cube.obj");
    this->m_embeddedModels[EmbeddedModel::CYLINDER] = std::make_shared<Model>("./assets/models/cylinder.obj");
    this->m_embeddedModels[EmbeddedModel::MONKEY] = std::make_shared<Model>("./assets/models/monkey.obj");
    this->m_embeddedModels[EmbeddedModel::SPHERE] = std::make_shared<Model>("./assets/models/sphere.obj");
}

void AssetManager::InitializeEmbeddedShaders()
{
    this->m_embeddedShaders.resize(EmbeddedShader::_EMBEDDED_SHADERS_ALL);
    this->m_embeddedShaders[EmbeddedShader::DEFAULT] = std::make_shared<Shader>(
        "default",
        "./assets/shaders/default.vert",
        "./assets/shaders/default.frag"
    );
}
