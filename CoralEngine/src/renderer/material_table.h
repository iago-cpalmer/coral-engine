#ifndef MATERIAL_TABLE_H
#define MATERIAL_TABLE_H

#include "data/material.h"

typedef struct
{
	std::vector<Material*> Materials;

} MaterialTable;

void add_material_to_table(MaterialTable* rp_material_table, Material* rp_material);
void delete_material_from_table(MaterialTable* rp_material_table, Material* rp_material);

#endif // !MATERIAL_TABLE_H


