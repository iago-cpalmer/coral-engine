#ifndef MESHES_H
#define MESHES_H

/// FILE TO CREATE MESH DATA ARRAYS TO AVOID HAVING THEM IN THE MAIN.CPP OCCUPYING LOTS OF SPACE

// ------------------------------------
// CUBE
// ------------------------------------
float VERTICES_CUBE[] = {
	// Front face	
	// Position        // Normal         // Texture   
	 0.0f, 0.0f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	 0.0f, 1.0f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
	 1.0f, 0.0f,  0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
	 1.0f, 1.0f,  0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
						
	 // Back face		
	 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
						
	 // Top face		
	 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
						
	 // Bottom face		
	 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
	 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
	 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
						
	 // Left face		
	 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
						
	 // Right face		
	 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	 0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
};

unsigned int INDICES_CUBE[] = {
	// Front face
	0, 3, 2, 0, 1, 3,

	// Back face
	4 , 7 , 5 , 4 ,6 , 7,

	// Top face
	8, 10, 11, 8, 9, 10,

	// Bottom face
	14,  13, 12, 12, 15, 14,

	// Left face
	16, 18, 19, 16, 17, 18,

	// Right face
	20, 23, 22, 20, 22, 21
};

#endif // !MESHES_H

// ------------------------------------
// PLANE
// ------------------------------------
float VERTICES_PLANE[] = {
	 0.0f, 0.0f,  0.0f,  0.0f, 0.0f,
	 0.0f, 1.0f,  0.0f,  0.0f, 1.0f,
	 1.0f, 0.0f,  0.0f,  1.0f, 0.0f,
	 1.0f, 1.0f,  0.0f,  1.0f, 1.0f
};

unsigned int INDICES_PLANE[] = {
	0, 3, 2, 0, 1, 3,
	1, 0, 3, 0, 2, 3
};