#include "asset_manager.hpp"


AssetManager &AssetManager::GetInstance()
{
    static AssetManager am;
    return am;
}


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


void AssetManager::AddModel(const std::string &name, const std::string &modelPath)
{
    std::shared_ptr<Model> model = std::make_shared<Model>(modelPath, name);

    this->m_allModels.emplace(name, model);
}


void AssetManager::AddShader(const std::string &name, const std::string &vrPath, const std::string &frPath)
{
    std::shared_ptr<Shader> shader = std::make_shared<Shader>(name, vrPath, frPath);

    this->m_allShaders.emplace(name, shader);
}


void AssetManager::InitializeEmbeddedModels()
{
    this->AddModel(std::string(CUBE_MODEL_NAME),     ".\\assets\\models\\cube.obj"); 
    this->AddModel(std::string(CYLINDER_MODEL_NAME), ".\\assets\\models\\cylinder.obj"); 
    this->AddModel(std::string(MONKEY_MODEL_NAME),   ".\\assets\\models\\monkey.obj"); 
    this->AddModel(std::string(SPHERE_MODEL_NAME),   ".\\assets\\models\\sphere.obj"); 
}

void AssetManager::InitializeEmbeddedShaders()
{
    this->AddShader(std::string(DEFAULT_SHADER_NAME), ".\\assets\\shaders\\default.vert", ".\\assets\\shaders\\default.frag");
    this->AddShader(std::string(LIT_SHADER_NAME),     ".\\assets\\shaders\\default.vert", ".\\assets\\shaders\\lit.frag");
}
