#include "model.hpp"


Model::Model(const fs::path &path, const std::string &name)
    : m_path(path), m_name(name)
{
    LOG_INFO("Loading model: {}", path.string())

    // Is the name already set ?
    if (this->m_name.empty())
        this->m_name = Filesystem::GetFileName(path);

    // Import .obj file
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        LOG_ERR("Couldn't load model: {}", importer.GetErrorString())
        return;
    }

    this->m_meshes = this->ProcessNode(scene->mRootNode, scene);

    LOG_INFO("Loaded model {}", this->m_name)
}


void Model::Render(Shader &shader) const
{
    // Render every mesh from this model
    for (Mesh mesh : this->m_meshes)
        mesh.Render(shader);
}


std::string Model::GetBeautifiedName() const
{
    std::string beautifiedName = this->m_name;
    beautifiedName[0] = toupper(beautifiedName[0]);

    std::regex pattern(".obj", std::regex_constants::icase);
    beautifiedName = std::regex_replace(beautifiedName, pattern, "");
    
    return beautifiedName;
}


std::vector<Mesh> Model::ProcessNode(aiNode *node, const aiScene *scene)
{
    std::vector<Mesh> meshes;

    // Process the node's meshes
    for(uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(this->ProcessMesh(mesh, scene));
    }

    // Do the same for each of its children
    for(uint32_t i = 0; i < node->mNumChildren; i++)
    {
        std::vector<Mesh> childMeshes = this->ProcessNode(node->mChildren[i], scene);
        meshes.insert(meshes.end(), childMeshes.begin(), childMeshes.end());
    }

    return meshes;
}


Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
    std::shared_ptr<ITexture> texture;
    std::vector<uint32_t>     indices;
    std::vector<Vertex>       vertices;

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
        
        texture = this->LoadAllTextures(material, scene);
    }

    return Mesh(vertices, indices, texture);
}


std::shared_ptr<ITexture> Model::LoadAllTextures(aiMaterial *material, const aiScene *scene)
{
    // "Simple" texture (only a diffuse map)
    if (this->IsSimpleTexture(material))
        return this->LoadTexture(material, scene, aiTextureType_DIFFUSE);
    // PBR
    else
    {
        // Load all texture maps from the assimp material
        std::shared_ptr<BasicTexture> diffuseMap  = this->LoadTexture(material, scene, aiTextureType_DIFFUSE);
        std::shared_ptr<BasicTexture> specularMap = this->LoadTexture(material, scene, aiTextureType_SPECULAR);
        // Fallback if there is no specular map in the material
        if (!specularMap)
            specularMap = this->LoadTexture(material, scene, aiTextureType_METALNESS);
        
        std::shared_ptr<BasicTexture> normalMap = this->LoadTexture(material, scene, aiTextureType_NORMALS);
        std::shared_ptr<BasicTexture> heightMap = this->LoadTexture(material, scene, aiTextureType_HEIGHT);

        return std::make_shared<PBRTexture>(
            diffuseMap,
            specularMap,
            normalMap,
            heightMap
        );
    }
}


std::shared_ptr<BasicTexture> Model::LoadTexture(aiMaterial *material, const aiScene *scene, aiTextureType aiTexType)
{
    if (!(material->GetTextureCount(aiTexType) > 0))
        return nullptr;

    aiString str;
    if (material->GetTexture(aiTexType, 0, &str) != AI_SUCCESS)
        return nullptr;
    

    std::string texPath = str.C_Str();
    // Check in the cache if the texture already exists
    if (this->m_textureCache.contains(texPath))
        return this->m_textureCache.at(texPath);
    
    const aiTexture *aiTex = scene->GetEmbeddedTexture(texPath.c_str());

    std::shared_ptr<BasicTexture> texture;
    if (aiTex->mHeight == 0) 
        // Compressed image data (PNG, JPEG...) 
        texture = std::make_shared<BasicTexture>(
            reinterpret_cast<unsigned char*>(aiTex->pcData),
            aiTex->mWidth, 
            this->TexTypeFromAssimp(aiTexType),
            this->m_name
        );
    else
        // Raw data
        texture = std::make_shared<BasicTexture>(
            reinterpret_cast<unsigned char*>(aiTex->pcData),
            this->TexTypeFromAssimp(aiTexType),
            this->m_name
        );

    // Add the texture to the cache 
    // so it can be reused later
    this->m_textureCache.emplace(texPath, texture);

    return texture;
}



bool Model::IsSimpleTexture(aiMaterial *material)
{
    for (aiTextureType type : this->m_supportedTextureTypes) {
        unsigned int texCount = material->GetTextureCount(type);

        if (type != aiTextureType_DIFFUSE && texCount > 0)
            return false;
    }

    return true;
}

TextureType Model::TexTypeFromAssimp(aiTextureType assimp)
{
    switch (assimp)
    {
    case aiTextureType_DIFFUSE:   return TextureType::DIFFUSE;
    case aiTextureType_SPECULAR:  return TextureType::SPECULAR;
    case aiTextureType_METALNESS: return TextureType::SPECULAR;
    case aiTextureType_NORMALS:   return TextureType::NORMAL;
    case aiTextureType_HEIGHT:    return TextureType::HEIGHT;
    default:                      return TextureType::INVALID;
    }
}

