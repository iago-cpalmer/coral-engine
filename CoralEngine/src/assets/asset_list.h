#ifndef ASSETS_LIST_H
#define ASSETS_LIST_H

typedef struct
{
	const char* Path;
} Asset;

// ------------------------------------
// Textures
// ------------------------------------

enum class TextureName
{
	CONTAINER,	// from container.jpg
	WALL,		// from wall.jpg
	LIGHT_PLANE_TEXTURE,

	COUNT
};



static Asset _TextureAssets[] =
{
	Asset{"res/images/container.jpg"},
	Asset{"res/images/wall.jpg"},
	Asset{"res/images/point_light.png"}
};

// ------------------------------------
// Models
// ------------------------------------

enum class ModelName
{
	BACKPACK,

	COUNT
};

static Asset _ModelAssets[] =
{
	Asset{"container.jpg"},
	Asset{"wall.jpg"},
};

// ------------------------------------
// Shaders
// ------------------------------------

enum class ShaderName
{
	BASIC_SHADER,
	LIGHT_SHADER,
	
	COUNT
};

typedef struct
{
	Asset Fragment;
	Asset Vertex;
} ShaderAsset;

static ShaderAsset _ShaderAssets[] =
{
	ShaderAsset{{"res/shaders/basic_shader.frag"}, {"res/shaders/basic_shader.vert"}},
	ShaderAsset{{"res/shaders/light_shader.frag"}, {"res/shaders/light_shader.vert"}}
};

#endif // !ASSETS_LIST_H
