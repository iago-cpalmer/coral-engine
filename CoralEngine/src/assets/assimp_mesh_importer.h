#ifndef ASSIMP_MESH_IMPORTER_H
#define ASSIMP_MESH_IMPORTER_H

#include "../renderer/data/mesh.h"
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void import_model(Mesh* rp_mesh, std::string r_path);

void process_node(aiNode* rp_node, const aiScene* rp_scene, Mesh* rp_mesh);
void process_mesh(aiMesh* rp_aiMesh, const aiScene* rp_scene, Mesh* rp_mesh);

#endif // !ASSIMP_MESH_IMPORTER_H
