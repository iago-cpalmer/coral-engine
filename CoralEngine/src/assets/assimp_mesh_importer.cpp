#include "assimp_mesh_importer.h"

#include <iostream>
#include "assets_handler.h"

static std::vector<Vertex> s_Vertices;
static std::vector<unsigned int> s_Indices;

void import_model(Model* rp_model, std::string r_path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(r_path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    rp_model->Meshes.reserve(scene->mNumMeshes);
    process_node(scene->mRootNode, scene, rp_model);
}

void process_node(aiNode* rp_node, const aiScene* rp_scene, Model* rp_model)
{
    if (rp_node->mChildren == nullptr)
    {
        return;
    }
    for (int i = 0; i < rp_node->mNumMeshes; i++)
    {
        process_mesh(rp_scene->mMeshes[rp_node->mMeshes[i]], rp_scene, rp_model);
    }

    for (int i = 0; i < rp_node->mNumChildren; i++)
    {
        process_node(rp_node->mChildren[i], rp_scene, rp_model);
    }

}

void process_mesh(aiMesh* rp_mesh, const aiScene* rp_scene, Model* rp_model)
{
    Mesh mesh = { 0 };
    
    s_Vertices.clear();
    if (s_Vertices.capacity() < rp_mesh->mNumVertices)
    {
        s_Vertices.reserve(rp_mesh->mNumVertices);
    }

    for (unsigned int i = 0; i < rp_mesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.Position.x = rp_mesh->mVertices[i].x;
        vertex.Position.y = rp_mesh->mVertices[i].y;
        vertex.Position.z = rp_mesh->mVertices[i].z;

        vertex.Normal.x = rp_mesh->mNormals[i].x;
        vertex.Normal.y = rp_mesh->mNormals[i].y;
        vertex.Normal.z = rp_mesh->mNormals[i].z;

        if (rp_mesh->mTextureCoords[0])
        {
            vertex.UV.x = rp_mesh->mTextureCoords[0][i].x;
            vertex.UV.y = rp_mesh->mTextureCoords[0][i].y;
        }
        else
        {
            vertex.UV = glm::vec2(0.0f, 0.0f);
        }

        s_Vertices.push_back(vertex);
    }

    s_Indices.clear();
    
    unsigned int indexCount = 0;
    for (unsigned int i = 0; i < rp_mesh->mNumFaces; i++)
    {
        indexCount += rp_mesh->mFaces[i].mNumIndices;
    }
    if (s_Indices.capacity() < indexCount)
    {
        s_Indices.reserve(indexCount);
    }

    for (unsigned int i = 0; i < rp_mesh->mNumFaces; i++)
    {
        aiFace face = rp_mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            s_Indices.push_back(face.mIndices[j]);
        }
    }

    Material mat;
    if (rp_mesh->mMaterialIndex >= 0)
    {
        mat.Shader = ah_get_shader_handle(ShaderName::BASIC_SHADER);
        aiMaterial* material = rp_scene->mMaterials[rp_mesh->mMaterialIndex];
        aiColor3D color(0.f, 0.f, 0.f);
        float shininess;

        material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        mat.Diffuse = glm::vec3(color.r, color.b, color.g);

        material->Get(AI_MATKEY_COLOR_AMBIENT, color);
        mat.Ambient = glm::vec3(color.r, color.b, color.g);

        material->Get(AI_MATKEY_COLOR_SPECULAR, color);
        mat.Specular = glm::vec3(color.r, color.b, color.g);

        material->Get(AI_MATKEY_SHININESS, shininess);
        mat.Shininess = shininess;
    }
    else
    {
        // mat = DEFAULT_MAT;
    }
}