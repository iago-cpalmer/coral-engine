#ifndef MESH_H
#define MESH_H

#include "texture.h"
#include "material.h"
#include "buffers/vertex_buffer_layout.h"
#include "buffers/vertex_array.h"

typedef struct
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 UV;
} Vertex;

typedef struct
{
	Material* Material;

	VertexArray Vao;
	VertexBuffer Vbo;
	IndexBuffer Ibo;

	int IndexCount;

} Mesh;


void create_mesh(Mesh* rpMesh, VertexAttribute* rVertexAttributes, int rVertexAttrCount, float* rVertices, int rVertexCount, unsigned int* rIndices, int rIndexCount, GLenum rUsage);

void release_mesh(Mesh* rpMesh);

#endif // !MESH_H
