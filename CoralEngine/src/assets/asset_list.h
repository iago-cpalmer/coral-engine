#ifndef ASSET_LIST_H
#define ASSET_LIST_H

typedef struct
{
	const char* Path;
} Asset;
typedef struct
{
	Asset Fragment;
	Asset Vertex;
} ShaderAsset;

// ------------------------------------
// Textures 
// ------------------------------------
enum class TextureName
{
	awesomeface,
	container,
	directional_light_icon,
	point_light,
	wall,
	leafs,
	stick,
	texture,
	COUNT
};
static Asset _TextureAssets[] =
{
	Asset{ "res/images/awesomeface.png"},
	Asset{ "res/images/container.jpg"},
	Asset{ "res/images/directional_light_icon.png"},
	Asset{ "res/images/point_light.png"},
	Asset{ "res/images/wall.jpg"},
	Asset{ "res/models/leafs.png"},
	Asset{ "res/models/stick.png"},
	Asset{ "res/models/texture.png"}
};

// ------------------------------------
// Shaders 
// ------------------------------------
enum class ShaderName
{
	basic_shader,
	light_shader,
	COUNT
};
static ShaderAsset _ShaderAssets[] =
{
	{ Asset{ "res/shaders/basic_shader.frag"}, Asset{ "res/shaders/basic_shader.vert"} },
	{ Asset{ "res/shaders/light_shader.frag"}, Asset{ "res/shaders/light_shader.vert"} }
};

// ------------------------------------
// Models 
// ------------------------------------
enum class ModelName
{
	backpack,
	//Car,
	//cube,
	//house,
	////stick,
	//tree,
	COUNT
};
static Asset _ModelAssets[] =
{
	Asset{ "res/models/backpack.fbx"}
	//Asset{ "res/models/stick.fbx"}
	//Asset{ "res/models/backpack.fbx"},
	//Asset{ "res/models/Car.fbx"},
	//Asset{ "res/models/cube.fbx"},
	//Asset{ "res/models/house.fbx"},
	//Asset{ "res/models/stick.fbx"},
	//Asset{ "res/models/tree.fbx"}
};
#endif // ASSET_LIST_H
