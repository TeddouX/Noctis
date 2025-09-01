#include "model_importer.hpp"

#include <unordered_map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <noctis/rendering/texture.hpp>
#include <noctis/rendering/mesh.hpp>
#include <noctis/rendering/model.hpp>
#include <noctis/logger.hpp>

#include "texture_importer.hpp"

namespace NoctisEditor
{

glm::mat4 AssimpToGlm(const aiMatrix4x4 &from);

std::vector<Noctis::Mesh> ProcessNode(
    aiNode *node, 
    const aiScene *scene, 
    Noctis::Mat4 parentMatrix);

Noctis::Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);

std::vector<std::shared_ptr<Noctis::Texture>> LoadAllTextures(
    aiMaterial *material, 
    const aiScene *scene);

std::shared_ptr<Noctis::Texture> LoadTexture(
    aiMaterial *material, 
    const aiScene *scene, 
    aiTextureType aiTexType, 
    std::unordered_map<std::string, std::shared_ptr<Noctis::Texture>> &textureCache);


std::unique_ptr<Noctis::Model> LoadModel(const fs::path &path)
{
    LOG_INFO("Loading model: {}", path.string());

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path.string(), aiProcess_Triangulate 
        | aiProcess_FlipUVs 
        | aiProcess_CalcTangentSpace
    );

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        LOG_ERR("Couldn't load model: {}", importer.GetErrorString());
        return nullptr;
    }

    return std::make_unique<Noctis::Model>(
        ProcessNode(scene->mRootNode, scene, Noctis::Mat4(1.f))
    );
}


glm::mat4 AssimpToGlm(const aiMatrix4x4 &from)
{
    glm::mat4 to;
    to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
    to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
    to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
    to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
    return to;
}


std::vector<Noctis::Mesh> ProcessNode(
    aiNode *node, 
    const aiScene *scene, 
    Noctis::Mat4 parentMatrix)
{
    std::vector<Noctis::Mesh> meshes;

    Noctis::Mat4 nodeTransform = parentMatrix * AssimpToGlm(node->mTransformation);

    // Process the node's meshes
    for(uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *assimpMesh = scene->mMeshes[node->mMeshes[i]];
        Noctis::Mesh mesh = ProcessMesh(assimpMesh, scene);
        mesh.SetTransformMatrix(nodeTransform);

        meshes.push_back(mesh);
    }

    // Do the same for each of its children
    for(uint32_t i = 0; i < node->mNumChildren; i++)
    {
        std::vector<Noctis::Mesh> childMeshes = ProcessNode(node->mChildren[i], scene, nodeTransform);
        meshes.insert(meshes.end(), childMeshes.begin(), childMeshes.end());
    }

    return meshes;
}


Noctis::Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
    std::shared_ptr<Noctis::Texture> texture;
    std::vector<uint32_t>    indices;
    std::vector<Noctis::Vertex>      vertices;

    // Process vertices
    for(uint32_t i = 0; i < mesh->mNumVertices; i++)
    {
        Noctis::Vertex vertex;

        Noctis::Vec3 vec3; 
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
            Noctis::Vec2 vec2;
            vec2.x = mesh->mTextureCoords[0][i].x; 
            vec2.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec2;
        }
        else
            vertex.texCoords = Noctis::Vec2(0.f);  
        
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
        
        LoadAllTextures(material, scene);
    }

    return Noctis::Mesh(vertices, indices);
}


std::vector<std::shared_ptr<Noctis::Texture>> LoadAllTextures(
    aiMaterial *material, 
    const aiScene *scene)
{
    static const std::array<aiTextureType, 5> supportedTextureTypes = {
        aiTextureType_DIFFUSE,
        aiTextureType_SPECULAR,
        aiTextureType_NORMALS,
        aiTextureType_HEIGHT
    };

    std::vector<std::shared_ptr<Noctis::Texture>> allTextures;
    std::unordered_map<std::string, std::shared_ptr<Noctis::Texture>> textureCache;
    for (auto texType : supportedTextureTypes)
    {
        if (auto tex = LoadTexture(material, scene, texType, textureCache))
            allTextures.push_back(tex);
    }

    return allTextures;
}


std::shared_ptr<Noctis::Texture> LoadTexture(
    aiMaterial *material, 
    const aiScene *scene, 
    aiTextureType aiTexType, 
    std::unordered_map<std::string, std::shared_ptr<Noctis::Texture>> &textureCache)
{
    if (!(material->GetTextureCount(aiTexType) > 0))
        return nullptr;

    aiString str;
    if (material->GetTexture(aiTexType, 0, &str) != AI_SUCCESS)
        return nullptr;
    

    std::string texPath = str.C_Str();
    // Check in the cache if the texture already exists
    if (textureCache.contains(texPath))
        return textureCache.at(texPath);
    
    const aiTexture *aiTex = scene->GetEmbeddedTexture(texPath.c_str());

    std::shared_ptr<Noctis::Texture> texture;
    if (aiTex->mHeight == 0)
        // Compressed image data (PNG, JPEG...) 
        texture = LoadTextureFromMemory(
            reinterpret_cast<uint8_t *>(aiTex->pcData),
            aiTex->mWidth
        );
    else
        // Raw data
        texture = std::make_shared<Noctis::Texture>(
            reinterpret_cast<uint8_t *>(aiTex->pcData),
            Noctis::IVec2(aiTex->mWidth, aiTex->mHeight)
        );

    // Add the texture to the cache 
    // so it can be reused later
    textureCache.emplace(texPath, texture);

    return texture;
}

}
