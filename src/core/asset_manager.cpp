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
    this->m_embeddedModels[EmbeddedModel::CUBE] = std::make_shared<Model>("Cube", R"(mtllib cube.mtl
o Cube
v 1.000000 -1.000000 -1.000000
v 1.000000 -1.000000 1.000000
v -1.000000 -1.000000 1.000000
v -1.000000 -1.000000 -1.000000
v 1.000000 1.000000 -0.999999
v 0.999999 1.000000 1.000001
v -1.000000 1.000000 1.000000
v -1.000000 1.000000 -1.000000
vt 1.000000 0.333333
vt 1.000000 0.666667
vt 0.666667 0.666667
vt 0.666667 0.333333
vt 0.666667 0.000000
vt 0.000000 0.333333
vt 0.000000 0.000000
vt 0.333333 0.000000
vt 0.333333 1.000000
vt 0.000000 1.000000
vt 0.000000 0.666667
vt 0.333333 0.333333
vt 0.333333 0.666667
vt 1.000000 0.000000
vn 0.000000 -1.000000 0.000000
vn 0.000000 1.000000 0.000000
vn 1.000000 0.000000 0.000000
vn -0.000000 0.000000 1.000000
vn -1.000000 -0.000000 -0.000000
vn 0.000000 0.000000 -1.000000
usemtl Material
s off
f 2/1/1 3/2/1 4/3/1
f 8/1/2 7/4/2 6/5/2
f 5/6/3 6/7/3 2/8/3
f 6/8/4 7/5/4 3/4/4
f 3/9/5 7/10/5 8/11/5
f 1/12/6 4/13/6 8/11/6
f 1/4/1 2/1/1 4/3/1
f 5/14/2 8/1/2 6/5/2
f 1/12/3 5/6/3 2/8/3
f 2/12/4 6/8/4 3/4/4
f 4/13/5 3/9/5 8/11/5
f 5/6/6 1/12/6 8/11/6
    )");
}

void AssetManager::InitializeEmbeddedShaders()
{
    this->m_embeddedShaders[EmbeddedShader::DEFAULT] = std::make_shared<Shader>("default",
        (const char *) R"(#version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aNormal;
        layout (location = 2) in vec2 aTexCoord;

        uniform mat4 Projection;
        uniform mat4 View;
        uniform mat4 Model;

        out vec2 TexCoord;
        out vec3 Normal;

        void main()
        {
            gl_Position = Projection * View * Model * vec4(aPos, 1.0);
            TexCoord = vec2(aTexCoord.x, 1 - aTexCoord.y);
            Normal = aNormal;
        })", 
        (const char *) R"(
        in vec2 TexCoord;

        out vec4 FragColor;

        uniform sampler2D Texture;

        void main()
        {
            // FragColor = texture(Texture, TexCoord);
            FragColor = vec4(1);
        })"
    );
}
