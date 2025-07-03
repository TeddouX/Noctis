#include "model_loader.hpp"


std::shared_ptr<Model> ModelLoader::LoadModel(const std::string &path)
{
    LOG_INFO("Loading model: {}", path);

    // Import .obj file
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        LOG_ERR("Couldn't load model: {}", importer.GetErrorString());
        return nullptr;
    }

    std::vector<Mesh> meshes = ModelLoader::ProcessNode(scene->mRootNode, scene);
    std::shared_ptr<Model> model = std::make_shared<Model>(meshes);

    return model;
}


std::vector<Mesh> ModelLoader::ProcessNode(aiNode *node, const aiScene *scene)
{
    std::vector<Mesh> meshes;

    // Process the node's meshes
    for(uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(ModelLoader::ProcessMesh(mesh, scene));
    }

    // Do the same for each of its children
    for(uint32_t i = 0; i < node->mNumChildren; i++)
    {
        std::vector<Mesh> childMeshes = ModelLoader::ProcessNode(node->mChildren[i], scene);
        meshes.insert(meshes.end(), childMeshes.begin(), childMeshes.end());
    }

    return meshes;
}


Mesh ModelLoader::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<Texture> textures;

    // Process vertices
    for(uint32_t i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        glm::vec3 vec3; 
        // Vertex position
        vec3.x = mesh->mVertices[i].x;
        vec3.y = mesh->mVertices[i].y;
        vec3.z = mesh->mVertices[i].z; 
        vertex.position = vec3;

        // Vertex normals
        vec3.x = mesh->mNormals[i].x;
        vec3.y = mesh->mNormals[i].y;
        vec3.z = mesh->mNormals[i].z;
        vertex.normal = vec3;  

        if(mesh->mTextureCoords[0]) // If the mesh has a texture 
        {
            glm::vec2 vec2;
            vec2.x = mesh->mTextureCoords[0][i].x; 
            vec2.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec2;
        }
        else
            vertex.texCoords = glm::vec2(0.0f, 0.0f);  
        
        vertices.push_back(vertex);
    }

    // Process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // Process material
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = ModelLoader::LoadTexturesFromMaterial(material, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
        
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    }

    return Mesh(vertices, indices, textures);
}


std::vector<Texture> ModelLoader::LoadTexturesFromMaterial(aiMaterial *material, aiTextureType type, TextureType texType)
{
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString str;
        material->GetTexture(type, i, &str);
    
        Texture texture(std::string(str.C_Str()), texType);
        textures.push_back(texture);
    }

    return textures;
}
