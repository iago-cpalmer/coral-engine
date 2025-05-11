#include "mesh.h"
#include <iostream>

void create_mesh(Mesh* rpMesh, VertexAttribute* rVertexAttributes, int rVertexAttrCount, float* rVertices, int rVertexCount, unsigned int* rIndices, int rIndexCount, GLenum rUsage)
{
	VertexBufferLayout layout = create_vertex_buffer_layout(rVertexAttributes, rVertexAttrCount);

	rpMesh->Vao = create_vao();
	rpMesh->Vbo = create_vbo(layout.Stride * rVertexCount, rVertices, rUsage);
	rpMesh->Ibo = create_ibo(rIndexCount * sizeof(unsigned int), rIndices, rUsage);

	vao_add_vbo(rpMesh->Vao, rpMesh->Vbo, layout);
	vao_add_ibo(rpMesh->Vao, rpMesh->Ibo);

	rpMesh->IndexCount = rIndexCount;
}

void release_mesh(Mesh* rpMesh)
{
	release_vao(rpMesh->Vao);
	release_vbo(rpMesh->Vbo);
	release_ibo(rpMesh->Ibo);
}
