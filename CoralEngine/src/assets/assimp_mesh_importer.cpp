#include "assimp_mesh_importer.h"

#include <iostream>
#include "assets_handler.h"

static std::vector<Vertex> s_Vertices;
static std::vector<unsigned int> s_Indices;

// TODO: this should maybe done in a better way?
static unsigned int s_SubmeshCount = 0;
static unsigned int s_TotalIndexCount = 0;
static unsigned int s_TotalVertexCount = 0;

void import_model(Mesh* rp_mesh, std::string r_path)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(r_path, aiProcess_Triangulate | aiProcess_FlipUVs);
    
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    VertexAttribute vertexAttributes[] =
    {
        VertexAttribute{VertexAttributeType::FLOAT, 3},	    // Position
        VertexAttribute{VertexAttributeType::FLOAT, 3},	    // Normal
        VertexAttribute{VertexAttributeType::FLOAT, 2}		// UV
    };

    /// vvv ---------------------------
    // TODO: should this be done here so it can allocate buffers for the mesh being created now
    // or it should be done after processing the whole mesh and then passing all data when
    // creating the mesh?
    unsigned int vertexCount = 0;
    unsigned int indexCount = 0;
    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        vertexCount += scene->mMeshes[i]->mNumVertices;
        indexCount += scene->mMeshes[i]->mNumFaces*3;
    }

    create_mesh(rp_mesh, vertexAttributes, 3, nullptr, vertexCount, nullptr, indexCount, scene->mNumMeshes, GL_STATIC_DRAW);
    // ^^^ ---------------------------

    s_SubmeshCount = 0;
    s_TotalIndexCount = 0;
    s_TotalVertexCount = 0;
    
    process_node(scene->mRootNode, scene, rp_mesh);
}

void process_node(aiNode* rp_node, const aiScene* rp_scene, Mesh* rp_mesh)
{
   
    for (int i = 0; i < rp_node->mNumMeshes; i++)
    {
        process_mesh(rp_scene->mMeshes[rp_node->mMeshes[i]], rp_scene, rp_mesh);
    }

    if (rp_node->mChildren == nullptr)
    {
        return;
    }

    for (int i = 0; i < rp_node->mNumChildren; i++)
    {
        process_node(rp_node->mChildren[i], rp_scene, rp_mesh);
    }

}

void process_mesh(aiMesh* rp_aiMesh, const aiScene* rp_scene, Mesh* rp_mesh)
{
    Mesh mesh = { 0 };
    
    int vertexCount = rp_aiMesh->mNumVertices;
    s_Vertices.clear();
    if (s_Vertices.capacity() < rp_aiMesh->mNumVertices)
    {
        s_Vertices.reserve(rp_aiMesh->mNumVertices);
    }

    for (unsigned int i = 0; i < rp_aiMesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.Position.x = rp_aiMesh->mVertices[i].x;
        vertex.Position.y = rp_aiMesh->mVertices[i].y;
        vertex.Position.z = rp_aiMesh->mVertices[i].z;

        if (rp_aiMesh->mNormals != NULL)
        {
            vertex.Normal.x = rp_aiMesh->mNormals[i].x;
            vertex.Normal.y = rp_aiMesh->mNormals[i].y;
            vertex.Normal.z = rp_aiMesh->mNormals[i].z;
        }
        

        if (rp_aiMesh->mTextureCoords[0])
        {
            vertex.UV.x = rp_aiMesh->mTextureCoords[0][i].x;
            vertex.UV.y = rp_aiMesh->mTextureCoords[0][i].y;
        }
        else
        {
            vertex.UV = glm::vec2(0.0f, 0.0f);
        }

        s_Vertices.push_back(vertex);
    }

    s_Indices.clear();
    
    unsigned int indexCount = 0;
    for (unsigned int i = 0; i < rp_aiMesh->mNumFaces; i++)
    {
        indexCount += rp_aiMesh->mFaces[i].mNumIndices;
    }
    if (s_Indices.capacity() < indexCount)
    {
        s_Indices.reserve(indexCount);
    }

    for (unsigned int i = 0; i < rp_aiMesh->mNumFaces; i++)
    {
        aiFace face = rp_aiMesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            s_Indices.push_back(face.mIndices[j] + s_TotalVertexCount);
        }
    }

    // TODO: this material should already be created with the external asset creator
    // in the asset_handler's material table
    Material meshMaterial;
    if (rp_aiMesh->mMaterialIndex >= 0)
    {
        //meshMaterial = ah_create_material();
        meshMaterial.Shader = ah_get_shader_handle(ShaderName::basic_shader);
        // TODO: the texture from the material should be added in the asset handler's texture table
        // on the external asset creator
        meshMaterial.AlbedoMap = ah_get_texture_handle(TextureName::container);
        aiMaterial* material = rp_scene->mMaterials[rp_aiMesh->mMaterialIndex];
        aiColor3D color(0.0f, 0.0f, 0.0f);
        float shininess;

        material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        meshMaterial.Diffuse = glm::vec3(color.r, color.b, color.g);

        material->Get(AI_MATKEY_COLOR_AMBIENT, color);
        meshMaterial.Ambient = glm::vec3(color.r, color.b, color.g);

        material->Get(AI_MATKEY_COLOR_SPECULAR, color);
        meshMaterial.Specular = glm::vec3(color.r, color.b, color.g);

        material->Get(AI_MATKEY_SHININESS, shininess);
        meshMaterial.Shininess = shininess;
    }
    else
    {
        // TODO: add default material
        //meshMaterial = DEFAULT_MAT;
    }

    vbo_set_data(rp_mesh->Vbo, s_Vertices.data(), sizeof(Vertex) * vertexCount, s_TotalVertexCount);
    ibo_set_data(rp_mesh->Ibo, s_Indices.data(), sizeof(unsigned int) * indexCount, s_TotalIndexCount);

    rp_mesh->Submeshes[s_SubmeshCount] = Submesh{ s_TotalIndexCount, indexCount };
    //TODO: rp_mesh->Materials[s_SubmeshCount] = meshMaterial;
    
    s_TotalIndexCount += indexCount;
    s_TotalVertexCount += vertexCount;
    ++s_SubmeshCount;
}