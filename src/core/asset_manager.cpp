#include "asset_manager.hpp"


AssetManager &AssetManager::GetInstance()
{
    static AssetManager am;
    return am;
}


void AssetManager::LoadEmbedded()
{
    this->InitializeEmbeddedModels();
    this->InitializeEmbeddedShaders();
}


void AssetManager::AddModel(const std::string &modelPath)
{
    auto model = std::make_shared<Model>(modelPath);
    
    this->AddAllTexturesFromModel(model);
    this->m_allModels.emplace(model->GetName(), model);
}


void AssetManager::AddModel(const std::string &name, const std::string &modelPath)
{
    std::shared_ptr<Model> model = std::make_shared<Model>(modelPath, name);

    this->AddAllTexturesFromModel(model);
    this->m_allModels.emplace(name, model);
}


void AssetManager::AddAllTexturesFromModel(std::shared_ptr<Model> model)
{
    // Get the texture cache from the model
    const auto &modelTextures = model->GetTextures();

    // Add all textures from the model to the registries
    for (auto texture : modelTextures)
        this->AddTexture(model->GetName(), texture);

    // Clear the model's cache because 
    // it is not needed anymore
    model->ClearTextures();
}


void AssetManager::AddShader(const std::string &name, const std::string &vrPath, const std::string &frPath)
{
    std::shared_ptr<Shader> shader = std::make_shared<Shader>(name, vrPath, frPath);

    this->m_allShaders.emplace(name, shader);
}


void AssetManager::InitializeEmbeddedModels()
{
    LOG_INFO("Loading embedded models.")
    
    this->AddModel(std::string(CUBE_MODEL_NAME),     ".\\assets\\models\\cube.obj"); 
    this->AddModel(std::string(CYLINDER_MODEL_NAME), ".\\assets\\models\\cylinder.obj"); 
    this->AddModel(std::string(MONKEY_MODEL_NAME),   ".\\assets\\models\\monkey.obj"); 
    this->AddModel(std::string(SPHERE_MODEL_NAME),   ".\\assets\\models\\sphere.obj"); 
}

void AssetManager::InitializeEmbeddedShaders()
{
    LOG_INFO("Loading embedded shaders.")
    
    this->AddShader(std::string(DEFAULT_SHADER_NAME), ".\\assets\\shaders\\default.vert", ".\\assets\\shaders\\default.frag");
    this->AddShader(std::string(LIT_SHADER_NAME),     ".\\assets\\shaders\\default.vert", ".\\assets\\shaders\\lit.frag");
}
