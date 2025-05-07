#ifndef ENTITY_H
#define ENTITY_H

#include <glm/vec3.hpp>
#include "../renderer/data/mesh.h"

typedef struct
{
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	// TODO: entities should have components. Then a mesh should be a component
	Mesh* p_Mesh;

} Entity;

#endif // !ENTITY_H
