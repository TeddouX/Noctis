#include "model.hpp"


TextureType TexTypeFromAssimp(aiTextureType assimp)
{
    switch (assimp)
    {
    case aiTextureType_DIFFUSE:  return TextureType::DIFFUSE;
    case aiTextureType_SPECULAR: return TextureType::SPECULAR;
    case aiTextureType_NORMALS:  return TextureType::NORMAL;
    case aiTextureType_HEIGHT:   return TextureType::HEIGHT;
    default:                     return TextureType::INVALID;
    }
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



Model::Model(const fs::path &path, const std::string &name)
    : m_path(path), m_name(name)
{
    LOG_INFO("Loading model: {}", path.string())

    // Is the name already set ?
    if (this->m_name.empty())
        this->m_name = Filesystem::GetFileName(path);

    // Import .obj file
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path.string(), aiProcess_Triangulate 
        | aiProcess_FlipUVs 
        | aiProcess_CalcTangentSpace
    );

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        LOG_ERR("Couldn't load model: {}", importer.GetErrorString())
        return;
    }

    this->m_meshes = this->ProcessNode(scene->mRootNode, scene, Mat4(1.f));
    
    // The texture cache is not needed 
    // anymore so we can safely clear it
    this->m_textureCache.clear();

    LOG_INFO("Loaded model {}", this->m_name)
}


void Model::Render(Shader &shader, const Mat4 &modelMatrix) const
{
    // Render every mesh from this model
    for (Mesh mesh : this->m_meshes)
        mesh.Render(shader, modelMatrix);
}


std::string Model::GetBeautifiedName() const
{
    std::string beautifiedName = this->m_name;
    beautifiedName[0] = toupper(beautifiedName[0]);

    std::regex pattern(".obj", std::regex_constants::icase);
    beautifiedName = std::regex_replace(beautifiedName, pattern, "");
    // Replace underscores with spaces
    beautifiedName = std::regex_replace(beautifiedName, std::regex("_"), " ");
    
    return beautifiedName;
}


std::vector<Mesh> Model::ProcessNode(aiNode *node, const aiScene *scene, Mat4 parentMatrix)
{
    std::vector<Mesh> meshes;

    Mat4 nodeTransform = parentMatrix * AssimpToGlm(node->mTransformation);

    // Process the node's meshes
    for(uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *assimpMesh = scene->mMeshes[node->mMeshes[i]];
        Mesh mesh = this->ProcessMesh(assimpMesh, scene);
        mesh.SetTransformMatrix(nodeTransform);

        meshes.push_back(mesh);
    }

    // Do the same for each of its children
    for(uint32_t i = 0; i < node->mNumChildren; i++)
    {
        std::vector<Mesh> childMeshes = this->ProcessNode(node->mChildren[i], scene, nodeTransform);
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
        
        this->LoadAllTextures(material, scene);
    }

    return Mesh(vertices, indices);
}


void Model::LoadAllTextures(aiMaterial *material, const aiScene *scene)
{
    // "Simple" texture (only a diffuse map)
    if (this->IsSimpleTexture(material))
    {
        std::shared_ptr<BasicTexture> basicTexture  = this->LoadTexture(material, scene, aiTextureType_DIFFUSE);
        
        this->m_textures.push_back(basicTexture);
    }
    // PBR
    else
    {
        // Load all texture maps from the assimp material
        std::shared_ptr<BasicTexture> diffuseMap  = this->LoadTexture(material, scene, aiTextureType_DIFFUSE);
        auto specularMap = this->LoadTexture(material, scene, aiTextureType_SPECULAR);
        // Fallback if there is no specular map in the material
        if (!specularMap)
            specularMap = this->LoadTexture(material, scene, aiTextureType_METALNESS);
        
        auto normalMap = this->LoadTexture(material, scene, aiTextureType_NORMALS);
        auto heightMap = this->LoadTexture(material, scene, aiTextureType_HEIGHT);
        
        auto pbrTexture = std::make_shared<PBRTexture>(
            this->m_name,
            diffuseMap,
            specularMap,
            normalMap,
            heightMap
        );

        this->m_textures.push_back(pbrTexture);
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
            TexTypeFromAssimp(aiTexType),
            this->m_name
        );
    else
        // Raw data
        texture = std::make_shared<BasicTexture>(
            reinterpret_cast<unsigned char*>(aiTex->pcData),
            TexTypeFromAssimp(aiTexType),
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
