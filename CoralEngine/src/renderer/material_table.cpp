#include "material_table.h"

void add_material_to_table(MaterialTable* rp_material_table, Material* rp_material)
{
	int freeSlot = -1;
	for (int i = 0; i < rp_material_table->Materials.size(); i++)
	{
		if (rp_material_table->Materials.at(i) == nullptr)
		{
			freeSlot = i;
		}
		else if (rp_material_table->Materials.at(i) == rp_material)
		{
			return;
		}
	}
	if (freeSlot == -1)
	{
		rp_material_table->Materials.push_back(rp_material);
	}
	else 
	{
		rp_material_table->Materials.at(freeSlot) = rp_material;
	}
}

void delete_material_from_table(MaterialTable* rp_material_table, Material* rp_material)
{
	for (int i = 0; i < rp_material_table->Materials.size(); i++)
	{
		if (rp_material_table->Materials.at(i) == rp_material)
		{
			rp_material_table->Materials.at(i) = nullptr;
		}
	}
}
