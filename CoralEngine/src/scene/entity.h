#ifndef ENTITY_H
#define ENTITY_H

#include <glm/vec3.hpp>
#include "../renderer/data/model.h"

typedef struct
{
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	// TODO: entities should have components. Then a mesh should be a component
	ModelHandle ModelHandle;

} Entity;

#endif // !ENTITY_H
