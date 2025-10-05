#ifndef MODEL_H
#define MODEL_H

#include "utils.h";
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
//#include "../../CoralEngine/vendor/glm/glm/ext/vector_float3.hpp"
//#include "../../CoralEngine/src/renderer/data/material.h"

std::vector<std::string> _Models;

int s_SubmeshCount{ 0 };

typedef struct
{
    std::vector<std::string> AlbedoTextureNames;
} Model;


void write_models(std::ofstream& r_outputFile)
{
    r_outputFile << "\n// ------------------------------------\n";
    r_outputFile << "// Models \n";
    r_outputFile << "// ------------------------------------\n";

    // Enum
    r_outputFile << "enum class ModelName\n";
    r_outputFile << "{\n";
    for (size_t i = 0; i < _Models.size(); i++)
    {
        r_outputFile << "\t" << get_asset_name(_Models[i]);
        r_outputFile << ",\n";
    }

    r_outputFile << "\tCOUNT\n";
    r_outputFile << "};\n";

    // Paths
    r_outputFile << "static Asset _ModelAssets[] =\n";
    r_outputFile << "{\n";

    for (size_t i = 0; i < _Models.size(); i++)
    {
        r_outputFile << "\tAsset{ \"" << _Models[i] << "\"}";
        if (i < _Models.size() - 1)
        {
            r_outputFile << ",";
        }
        r_outputFile << "\n";
    }
    r_outputFile << "}; \n";
}

//
//void process_mesh(aiMesh* rp_aiMesh, const aiScene* rp_scene, Model* rp_model)
//{
//   // TODO: this material should already be created with the external asset creator
//    // in the asset_handler's material table
//    Material meshMaterial;
//    if (rp_aiMesh->mMaterialIndex >= 0)
//    {
//        //meshMaterial = ah_create_material();
//         
//        // TODO: the texture from the material should be added in the asset handler's texture table
//        // on the external asset creator
//        aiMaterial* material = rp_scene->mMaterials[rp_aiMesh->mMaterialIndex];
//       
//        // Get texture strings
//        for(int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++)
//        {
//            aiString str;
//            material->GetTexture(aiTextureType_DIFFUSE, i, &str);
//
//            rp_model->AlbedoTextureNames.push_back(str.C_Str());
//        }
//    }
//
//    //rp_mesh->Materials[s_SubmeshCount] = meshMaterial;
//
//    ++s_SubmeshCount;
//}
//
//void process_node(aiNode* rp_node, const aiScene* rp_scene, Model* rp_model)
//{
//
//    for (int i = 0; i < rp_node->mNumMeshes; i++)
//    {
//        process_mesh(rp_scene->mMeshes[rp_node->mMeshes[i]], rp_scene, rp_model);
//    }
//
//    if (rp_node->mChildren == nullptr)
//    {
//        return;
//    }
//
//    for (int i = 0; i < rp_node->mNumChildren; i++)
//    {
//        process_node(rp_node->mChildren[i], rp_scene, rp_model);
//    }
//
//}
//
//void process_model(std::string r_path)
//{
//    // Load all models and get its textures paths to add them to the _Textures vector
//
//    Assimp::Importer importer;
//    const aiScene* scene = importer.ReadFile(r_path, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//    {
//        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
//        return;
//    }
//
//    Model model;
//    process_node(scene->mRootNode, scene, &model);
//}
//
//void process_models()
//{
//    for (size_t i = 0; i < _Models.size(); i++)
//    {
//        s_SubmeshCount = 0;
//        process_model(_Models[i]);
//    }
//}

#endif // !MODEL_H
