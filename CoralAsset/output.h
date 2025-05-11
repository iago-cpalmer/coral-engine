#ifndef ASSET_LIST_H
#define ASSET_LIST_H

typedef struct
{
 	const char* Path
} Asset;
typedef struct
{
 	Asset Fragment
 	Asset Vertex
} ShaderAsset;

// ------------------------------------
// Textures 
// ------------------------------------
enum class TextureNames
{
	awesomeface,
	container,
	directional_light_icon,
	point_light,
	wall,
	leafs,
	stick,
	texture
};
static Asset _TextureAssets[] =
{
	Asset{ "res\images\awesomeface.png "},
	Asset{ "res\images\container.jpg "},
	Asset{ "res\images\directional_light_icon.png "},
	Asset{ "res\images\point_light.png "},
	Asset{ "res\images\wall.jpg "},
	Asset{ "res\models\leafs.png "},
	Asset{ "res\models\stick.png "},
	Asset{ "res\models\texture.png "}
}; 

// ------------------------------------
// Shaders 
// ------------------------------------
enum class ShaderNames
{
	basic_shader
};
static ShaderAsset _ShaderAssets[] =
{
	{ Asset{ "res/shaders/basic_shader.frag"}, Asset{ "res/shaders/basic_shader.vert"}
}; 
#endif // ASSET_LIST_H
