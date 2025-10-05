#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "../../CoralEngine/vendor/glm/glm/ext/vector_float3.hpp"
typedef struct
{
	std::string AlbedoMapName;

	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float Shininess;


} Material;

#endif // !MATERIAL_H