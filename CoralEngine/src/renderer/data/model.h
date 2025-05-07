#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include <vector>

typedef struct
{
	std::vector<Mesh> Meshes;
} Model;

typedef struct
{
	unsigned int Id;
} ModelHandle;

void create_model(Model* rp_model, int r_numberOfMeshes);

void release_model(Model* rp_model);

#endif