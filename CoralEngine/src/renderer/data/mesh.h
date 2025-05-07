#ifndef MESH_H
#define MESH_H

#include "texture.h"
#include "material.h"

typedef struct
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 UV;
} Vertex;

typedef struct
{
	Material* Material;

	unsigned int Vao;
	unsigned int Vbo;
	unsigned int Ebo;

	int NrIndices;

} Mesh;

// (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
typedef struct
{
	GLint SizeOfType;
	GLint Count;
	GLenum Type;
} VertexAttribute;

void create_mesh(Mesh* rpMesh, VertexAttribute* rVertexAttributes, int rVertexAttrCount, float* rVertices, int rVertexCount, unsigned int* rIndices, int rIndexCount, GLenum rUsage);

void release_mesh(Mesh* rpMesh);

#endif // !MESH_H
