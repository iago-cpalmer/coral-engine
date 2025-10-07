#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

typedef struct
{
	unsigned int Texture;
	int Width, Height, NrChannels;
} Texture;

typedef struct
{
	unsigned int Id;
	unsigned int GenerationId;
} TextureHandle;


void create_texture(Texture* rpTexture, const char* rPath);

void use_texture(Texture* rpTexture);


#endif // !TEXTURE_H
