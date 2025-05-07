#include "mesh.h"

void create_mesh(Mesh* rpMesh, VertexAttribute* rVertexAttributes, int rVertexAttrCount, float* rVertices, int rVertexCount, unsigned int* rIndices, int rIndexCount, GLenum rUsage)
{
	// Set vertex attributes
	int stride = 0;
	int countOfElements = 0;
	for (size_t i = 0; i < rVertexAttrCount; i++)
	{
		stride += rVertexAttributes[i].SizeOfType * rVertexAttributes[i].Count;
		countOfElements += rVertexAttributes[i].Count;
	}

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ((size_t)rVertexCount * countOfElements), rVertices, rUsage);

	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * rIndexCount, rIndices, rUsage);

	int accOffset = 0;
	for (int i = 0; i < rVertexAttrCount; i++)
	{
		glVertexAttribPointer(i, rVertexAttributes[i].Count, rVertexAttributes[i].Type, GL_FALSE, stride, (void*)accOffset);
		glEnableVertexAttribArray(i);
		accOffset += rVertexAttributes[i].SizeOfType * rVertexAttributes[i].Count;
	}

	rpMesh->Vao = vao;
	rpMesh->Vbo = vbo;
	rpMesh->Ebo = ebo;
	rpMesh->NrIndices = rIndexCount;
}

void release_mesh(Mesh* rpMesh)
{
	glDeleteBuffers(3, &rpMesh->Vao);
}
