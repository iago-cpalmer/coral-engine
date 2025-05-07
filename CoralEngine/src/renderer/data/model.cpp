#include "model.h"

void create_model(Model* rp_model, int r_numberOfMeshes)
{
	rp_model->Meshes.reserve(r_numberOfMeshes);
}

void release_model(Model* rp_model)
{
	rp_model->Meshes.clear();
}
