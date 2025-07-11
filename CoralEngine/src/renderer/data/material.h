#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/vec3.hpp>
#include "shader.h"
#include "texture.h"

typedef struct
{
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float Shininess;

	ShaderHandle Shader;

	TextureHandle AlbedoMap;
}Material;

typedef struct
{
	unsigned int Id;
} MaterialHandle;

#endif // !MATERIAL_H
