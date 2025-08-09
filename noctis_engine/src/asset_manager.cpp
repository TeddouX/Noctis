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


void AssetManager::AddModel(Model &model)
{
    this->AddAllTexturesFromModel(model);
    this->m_allModels.emplace(model.GetName(), model);
}


void AssetManager::AddAllTexturesFromModel(Model &model)
{
    // Get the texture cache from the model
    const auto &modelTextures = model.GetTextures();

    // Add all textures from the model to the registries
    for (auto texture : modelTextures)
        this->AddTexture(model.GetName(), texture);

    // Clear the model's cache because 
    // it is not needed anymore
    model.ClearTextures();
}


void AssetManager::AddShader(Shader &shader)
{
    this->m_allShaders.emplace(shader.GetName(), shader);
}



std::shared_ptr<Model> AssetManager::GetModel(const std::string &name)
{
    return std::make_shared<Model>(this->m_allModels.at(name));
}


std::shared_ptr<Shader> AssetManager::GetShader(const std::string &name)
{

    return std::make_shared<Shader>(this->m_allShaders.at(name));
}


std::shared_ptr<ITexture> AssetManager::GetTexture(const std::string &name)
{

    return m_allTextures.at(name);
}


void AssetManager::InitializeEmbeddedModels()
{
    LOG_INFO("Loading embedded models.");
    
    Model cubeModel = Model(".\\assets\\models\\cube.obj", std::string(CUBE_MODEL_NAME));
    Model cylinderModel = Model(".\\assets\\models\\cylinder.obj", std::string(CYLINDER_MODEL_NAME));
    Model monkeyModel = Model(".\\assets\\models\\monkey.obj", std::string(MONKEY_MODEL_NAME));
    Model sphereModel = Model(".\\assets\\models\\sphere.obj", std::string(SPHERE_MODEL_NAME));

    this->AddModel(cubeModel); 
    this->AddModel(cylinderModel); 
    this->AddModel(monkeyModel); 
    this->AddModel(sphereModel); 
}

void AssetManager::InitializeEmbeddedShaders()
{
    LOG_INFO("Loading embedded shaders.");
    
    Shader defaultShader = Shader(
        std::string(DEFAULT_SHADER_NAME),
        ".\\assets\\shaders\\default.vert", 
        ".\\assets\\shaders\\default.frag"
    );

    Shader litShader = Shader(
        std::string(LIT_SHADER_NAME),
        ".\\assets\\shaders\\default.vert", 
        ".\\assets\\shaders\\lit.frag"
    );

    this->AddShader(defaultShader);
    this->AddShader(litShader);
}
